#include "home.h"
#include "ui_home.h"
#include "login.h"

#include <QTimer>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidgetItem>
#include <algorithm>
#include <QFileDialog>
#include <QThread>
#include <QEvent>
#include <QCryptographicHash>
#include <QRandomGenerator>

#include "pdfexportworker.h"
#include "databaseloader.h"

// Utility functions to convert hardware IDs
QString convertHwidToFriendlyId(const QString &hwid) {
    QString friendly = hwid;
    std::reverse(friendly.begin(), friendly.end());
    if (friendly.length() > 10) {
        friendly = friendly.left(10);
    }
    return friendly;
}

QString convertFriendlyIdToHwid(const QString &friendlyId) {
    QString hwid = friendlyId;
    std::reverse(hwid.begin(), hwid.end());
    return hwid;
}

home::home(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::home)
    , activityChartView(nullptr)
    , userStatusChartWidget(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("ARCHIFLOW 1.0.0 Beta");
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    applyShadowEffect();

    // Set up table columns for employee data
    QStringList headers = {"User ID", "Role", "Status", "Password", "Actions"};
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setSortingEnabled(true);

    connect(ui->tableWidget->horizontalHeader(), &QHeaderView::sectionClicked,
            this, &home::onTableHeaderSectionClicked);

    // Setup a timer to display current time
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        ui->label_2->setText(QDateTime::currentDateTime().toString("hh:mm:ss"));
    });
    timer->start(1000);

    connect(ui->tableWidget, &QTableWidget::cellDoubleClicked,
            this, &home::handleStatusToggle);

    connect(ui->exportpdf, &QPushButton::clicked,
            this, &home::exportPdf);


    if (!connectToDatabase()) {
        QMessageBox::critical(this, "Database Error", "Failed to connect to the database.");
    } else {
        startDatabaseLoading();
    }

    connect(ui->whitelist_table, &QTableWidget::itemChanged,
            this, &home::onWhitelistItemChanged);

    setupActivityChart();
    setupUserStatusChart();

    QTimer *statusTimer = new QTimer(this);
    connect(statusTimer, &QTimer::timeout, this, &home::recordUserStatusSnapshot);
    statusTimer->start(60000); // every minute

    updateWhitelistTable();
}

home::~home()
{
    delete ui;
}

bool home::connectToDatabase()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Oracle in XE};DBQ=XE;UID=DALI;PWD=dali;");
    if (!db.open()) {
        qDebug() << "Database connection error:" << db.lastError().text();
        return false;
    }
    return true;
}

void home::applyShadowEffect()
{
    auto createShadow = [](QWidget *widget) {
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(widget);
        shadow->setBlurRadius(15);
        shadow->setOffset(4, 4);
        shadow->setColor(QColor(0, 0, 0, 80));
        widget->setGraphicsEffect(shadow);
    };

    createShadow(ui->tableWidget);
    if (ui->activityLogList) createShadow(ui->activityLogList);
    if (ui->frame_2) createShadow(ui->frame_2);
    if (ui->frame_4) createShadow(ui->frame_4);
    if (ui->whitelist_table) createShadow(ui->whitelist_table);
    if (ui->frame_3) createShadow(ui->frame_3);

}

void home::logActivity(const QString &activity)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    ui->activityLogList->addItem(QString("%1: %2").arg(timestamp, activity));

    // Update the activity chart
    QTimer::singleShot(100, this, &home::updateActivityChart);
}

void home::startDatabaseLoading()
{
    QThread *thread = new QThread;
    DatabaseLoader *loader = new DatabaseLoader;
    loader->moveToThread(thread);
    connect(thread, &QThread::started, loader, &DatabaseLoader::process);
    connect(loader, &DatabaseLoader::finished, this, [=](const QList<QVariantMap> &records) {
        updateEmployeeTable(records);
        updateUserCounts();
        logActivity("Loaded employee records asynchronously.");
        thread->quit();
    });
    connect(loader, &DatabaseLoader::error, this, [=](const QString &errMsg) {
        QMessageBox::critical(this, "Database Loading Error", errMsg);
        thread->quit();
    });
    connect(loader, &DatabaseLoader::finished, loader, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    thread->start();
}

// ------------------ Employee Table ------------------

void home::updateEmployeeTable(const QList<QVariantMap> &records)
{
    ui->tableWidget->setRowCount(0);

    for (const QVariantMap &record : records) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(record["userId"].toString()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(record["role"].toString()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(record["status"].toString()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(record["password_hash"].toString()));

        QWidget *actionWidget = new QWidget;
        QHBoxLayout *layout = new QHBoxLayout(actionWidget);
        layout->setContentsMargins(0, 0, 0, 0);

        QPushButton *editButton = new QPushButton("Edit", actionWidget);
        editButton->setObjectName("editButton");
        QPushButton *deleteButton = new QPushButton("Delete", actionWidget);
        deleteButton->setObjectName("deleteButton");

        layout->addWidget(editButton);
        layout->addWidget(deleteButton);
        actionWidget->setLayout(layout);
        ui->tableWidget->setCellWidget(row, 4, actionWidget);

        connect(editButton, &QPushButton::clicked, this, &home::handleEditButton);
        connect(deleteButton, &QPushButton::clicked, this, &home::handleDeleteButton);
    }
}

void home::onTableHeaderSectionClicked(int index)
{
    if (index == 3) {
        bool currentlyHidden = ui->tableWidget->isColumnHidden(3);
        ui->tableWidget->setColumnHidden(3, !currentlyHidden);
    }
}

void home::updateCurrentUserStatus(const QString &status)
{
    // Generate the friendly ID from the current user's HWID
    QString friendlyId = login::convertHwidToFriendlyId(login::getHwid());

    QSqlQuery query(db);
    query.prepare("UPDATE empl SET status = :status WHERE user_id = :id");
    query.bindValue(":status", status);
    query.bindValue(":id", friendlyId);
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    // Update UI
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        QTableWidgetItem *idItem = ui->tableWidget->item(i, 0);
        if (idItem && idItem->text() == friendlyId) {
            QTableWidgetItem *statusItem = ui->tableWidget->item(i, 2);
            if (statusItem) {
                statusItem->setText(status);
            }
            break;
        }
    }
    updateUserCounts();
    logActivity(QString("Set status for %1 to %2").arg(friendlyId, status));
}

// ------------------ Buttons ------------------

void home::on_pushButton_4_clicked()
{
    logActivity("Closed window.");
    this->close();
}

void home::on_pushButton_5_clicked()
{
    logActivity("Minimized window.");
    this->showMinimized();
}

void home::on_pushButton_2_clicked()
{
    QString searchText = ui->lineEdit_5->text().trimmed();
    int searchColumn = ui->comboBox->currentIndex();

    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QTableWidgetItem *item = ui->tableWidget->item(row, searchColumn);
        if (item) {
            bool match = item->text().contains(searchText, Qt::CaseInsensitive);
            ui->tableWidget->setRowHidden(row, !match);
        }
    }
    logActivity(QString("Searched for '%1'.").arg(searchText));
}

void home::on_pushButton_3_clicked()
{
    QString hwid = login::getHwid();
    QString userRef = convertHwidToFriendlyId(hwid);
    qDebug() << "Generated HWID:" << hwid;
    qDebug() << "Generated friendly userRef:" << userRef;

    QString role = ui->lineEdit_3->text().trimmed();
    QString plainPassword = ui->lineEdit_6->text().trimmed();
    if (role.isEmpty() || plainPassword.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Role and password cannot be empty.");
        return;
    }

    QString status = "Offline";


    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT COUNT(*) FROM empl WHERE user_id = :id");
    checkQuery.bindValue(":id", userRef);
    if (!checkQuery.exec()) {
        QMessageBox::critical(this, "Database Error", checkQuery.lastError().text());
        return;
    }
    int count = 0;
    if (checkQuery.next()) {
        count = checkQuery.value(0).toInt();
    }
    if (count > 0) {
        QMessageBox::warning(this, "Input Error", "This user already exists.");
        return;
    }


    QString passwordHash = QString(
        QCryptographicHash::hash(plainPassword.toUtf8(), QCryptographicHash::Sha256).toHex()
        );


    if (!db.transaction()) {
        QMessageBox::critical(this, "Transaction Error", "Failed to start database transaction.");
        return;
    }

    QSqlQuery insertQuery(db);
    insertQuery.prepare(
        "INSERT INTO empl (user_id, hwid, role, status, password_hash) "
        "VALUES (:id, :hwid, :role, :status, :pass)"
        );
    insertQuery.bindValue(":id", userRef);
    insertQuery.bindValue(":hwid", hwid);
    insertQuery.bindValue(":role", role);
    insertQuery.bindValue(":status", status);
    insertQuery.bindValue(":pass", passwordHash);

    if (!insertQuery.exec()) {
        db.rollback();
        QMessageBox::critical(this, "Database Error", insertQuery.lastError().text());
        return;
    }
    if (!db.commit()) {
        QMessageBox::critical(this, "Transaction Error", "Failed to commit transaction.");
        return;
    }

    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(userRef));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(role));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(status));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(passwordHash));

    QWidget *actionWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(actionWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    QPushButton *editButton = new QPushButton("Edit", actionWidget);
    editButton->setObjectName("editButton");
    QPushButton *deleteButton = new QPushButton("Delete", actionWidget);
    deleteButton->setObjectName("deleteButton");
    layout->addWidget(editButton);
    layout->addWidget(deleteButton);
    actionWidget->setLayout(layout);
    ui->tableWidget->setCellWidget(0, 4, actionWidget);

    connect(editButton, &QPushButton::clicked, this, &home::handleEditButton);
    connect(deleteButton, &QPushButton::clicked, this, &home::handleDeleteButton);

    updateUserCounts();
    logActivity(QString("Added user %1.").arg(userRef));

    ui->lineEdit_3->clear();
    ui->lineEdit_6->clear();

    QMessageBox::information(this, "Add User", "User added successfully!");
}


void home::handleEditButton()
{


    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int rowToEdit = -1;
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QWidget *cellWidget = ui->tableWidget->cellWidget(row, 4);
        if (!cellWidget) continue;
        if (cellWidget->findChild<QPushButton*>("editButton") == button) {
            rowToEdit = row;
            break;
        }
    }
    if (rowToEdit < 0) return;

    QString newRole = ui->tableWidget->item(rowToEdit, 1)->text().trimmed();

    QString newPass = ui->tableWidget->item(rowToEdit, 3)->text().trimmed();


    QString currentStatus = ui->tableWidget->item(rowToEdit, 2)->text();
    QString userId = ui->tableWidget->item(rowToEdit, 0)->text();

    QString passHashToUse;
    if (!newPass.isEmpty()) {
        passHashToUse = QString(
            QCryptographicHash::hash(newPass.toUtf8(), QCryptographicHash::Sha256).toHex()
            );
    } else {
        passHashToUse = ui->tableWidget->item(rowToEdit, 3)->text();
    }

    QSqlQuery query(db);
    query.prepare(R"(
        UPDATE empl
           SET role          = :role,
               status        = :status,
               password_hash = :pass
         WHERE user_id       = :id
    )");
    query.bindValue(":role",   newRole);
    query.bindValue(":status", currentStatus);
    query.bindValue(":pass",   passHashToUse);
    query.bindValue(":id",     userId);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    ui->tableWidget->item(rowToEdit, 1)->setText(newRole);
    ui->tableWidget->item(rowToEdit, 3)->setText(passHashToUse);

    QMessageBox::information(this, "Edit Employee", "Employee updated successfully.");
    updateUserCounts();
    logActivity(QString("Edited user %1.").arg(userId));
}


void home::handleDeleteButton()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int rowToDelete = -1;
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QWidget *cellWidget = ui->tableWidget->cellWidget(row, 4);
        if (!cellWidget) continue;
        if (cellWidget->findChild<QPushButton*>("deleteButton") == button) {
            rowToDelete = row;
            break;
        }
    }
    if (rowToDelete < 0) return;

    QString userId = ui->tableWidget->item(rowToDelete, 0)->text();

    QSqlQuery query(db);
    query.prepare("DELETE FROM empl WHERE user_id = :id");
    query.bindValue(":id", userId);
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    ui->tableWidget->removeRow(rowToDelete);
    QMessageBox::information(this, "Delete Employee", "Employee deleted successfully.");
    updateUserCounts();
    logActivity(QString("Deleted user %1.").arg(userId));
}

void home::handleStatusToggle(int row, int column)
{
    if (column != 2) return;
    QTableWidgetItem *item = ui->tableWidget->item(row, column);
    if (!item) return;

    QString currentStatus = item->text();
    QString newStatus = (currentStatus.compare("Online", Qt::CaseInsensitive) == 0) ? "Offline" : "Online";
    item->setText(newStatus);

    QString userId = ui->tableWidget->item(row, 0)->text();
    QSqlQuery query(db);
    query.prepare("UPDATE empl SET status = :status WHERE user_id = :id");
    query.bindValue(":status", newStatus);
    query.bindValue(":id", userId);
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }
    updateUserCounts();
    logActivity(QString("Changed status for %1 to %2.").arg(userId, newStatus));
}

void home::updateUserCounts()
{
    int onlineCount = 0;
    int offlineCount = 0;
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        QTableWidgetItem *statusItem = ui->tableWidget->item(i, 2);
        if (!statusItem) continue;
        if (statusItem->text().compare("Online", Qt::CaseInsensitive) == 0) {
            onlineCount++;
        } else if (statusItem->text().compare("Offline", Qt::CaseInsensitive) == 0) {
            offlineCount++;
        }
    }
    ui->nbr_online->setText(QString::number(onlineCount));
    ui->nbr_offline->setText(QString::number(offlineCount));

    userStatusHistory[QDateTime::currentDateTime()] = qMakePair(onlineCount, offlineCount);
    updateUserStatusChart();
}


void home::on_whitelist_user_clicked()
{
    QString whidText = ui->hwid->text().trimmed();
    if (whidText.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a HWID to whitelist.");
        return;
    }

    int permission = 1;

    QString hwid = QString(QCryptographicHash::hash(whidText.toUtf8(), QCryptographicHash::Sha256).toHex());
    QSqlQuery query(db);

    query.prepare("INSERT INTO WHITELISTED_USERS (HWID, PERMISSION) VALUES (:hwid, :perm)");
    query.bindValue(":hwid", hwid);
    query.bindValue(":perm", permission);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Whitelist", "HWID whitelisted successfully.");
    ui->hwid->clear();

    updateWhitelistTable();

    logActivity(QString("Whitelisted HWID: %1 with permission %2").arg(whidText).arg(permission));
}

void home::updateWhitelistTable()
{
    ui->whitelist_table->blockSignals(true);

    ui->whitelist_table->setRowCount(0);

    QSqlQuery query(db);
    if (!query.exec("SELECT HWID, PERMISSION FROM WHITELISTED_USERS")) {
        qDebug() << "Error loading whitelist:" << query.lastError().text();
        ui->whitelist_table->blockSignals(false);
        return;
    }

    while (query.next()) {
        int row = ui->whitelist_table->rowCount();
        ui->whitelist_table->insertRow(row);
        QString hwid = query.value("HWID").toString();
        int perm = query.value("PERMISSION").toInt();

        ui->whitelist_table->setItem(row, 0, new QTableWidgetItem(hwid));
        ui->whitelist_table->setItem(row, 1, new QTableWidgetItem(QString::number(perm)));
    }

    ui->whitelist_table->blockSignals(false);
}

void home::onWhitelistItemChanged(QTableWidgetItem *item)
{
    int row = item->row();
    int column = item->column();

    if (column != 1) return;

    QString hwid = ui->whitelist_table->item(row, 0)->text();
    QString newPermStr = item->text().trimmed();
    bool ok = false;
    int newPerm = newPermStr.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Invalid Input", "Permission must be an integer.");
        updateWhitelistTable(); // revert changes
        return;
    }

    // Update the database
    QSqlQuery query(db);
    query.prepare("UPDATE WHITELISTED_USERS SET PERMISSION = :perm WHERE HWID = :hwid");
    query.bindValue(":perm", newPerm);
    query.bindValue(":hwid", hwid);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        updateWhitelistTable(); // revert changes
        return;
    }

    // Optionally refresh table
    updateWhitelistTable();

    logActivity(QString("Updated whitelist user %1 to permission %2").arg(hwid).arg(newPerm));
}

// ------------------ Export PDF ------------------

void home::on_save_clicked()
{
    QString pdfPath = QFileDialog::getSaveFileName(this, "Select Save Path", "", "PDF Files (*.pdf)");
    if (!pdfPath.isEmpty()) {
        ui->pathtosave->setText(pdfPath);
        logActivity(QString("Selected save path: '%1'.").arg(pdfPath));
    }
}

void home::exportPdf()
{
    QString pdfPath = ui->pathtosave->text().trimmed();
    if (pdfPath.isEmpty()) {
        QMessageBox::warning(this, "Export PDF", "Please select a save path using the Save button.");
        return;
    }

    QString html;
    html.append("<html><head><meta charset='UTF-8'></head><body>");
    html.append("<h2>Employee Data</h2>");
    html.append("<table border='1' cellspacing='0' cellpadding='2'>");
    html.append("<tr>");

    QStringList headers = {"User ID", "Role", "Status", "Password", "Actions"};
    for (const QString &header : headers) {
        html.append("<th>" + header + "</th>");
    }
    html.append("</tr>");

    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        html.append("<tr>");
        for (int j = 0; j < ui->tableWidget->columnCount(); ++j) {
            QTableWidgetItem *item = ui->tableWidget->item(i, j);
            QString cellText = (item ? item->text() : "");
            html.append("<td>" + cellText + "</td>");
        }
        html.append("</tr>");
    }
    html.append("</table></body></html>");

    bool compressionOn = ui->radioButton1compressionon->isChecked();

    QThread *thread = new QThread;
    PdfExportWorker *worker = new PdfExportWorker(pdfPath, html, compressionOn);
    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &PdfExportWorker::process);
    connect(worker, &PdfExportWorker::finished, this, [=]() {
        QMessageBox::information(this, "Export PDF", "PDF exported successfully.");
        logActivity(QString("Exported PDF to '%1'. Compression %2.")
                        .arg(pdfPath).arg(compressionOn ? "ON" : "OFF"));
        thread->quit();
    });
    connect(worker, &PdfExportWorker::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(worker, &PdfExportWorker::error, this, [=](const QString &errMsg) {
        QMessageBox::critical(this, "Export PDF Error", errMsg);
        thread->quit();
    });
    thread->start();
}

void home::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::ActivationChange) {
        if (this->isActiveWindow())
            updateCurrentUserStatus("Online");
        else
            updateCurrentUserStatus("Offline");
    }
    QWidget::changeEvent(event);
}

// ----- Activity Chart -----
void home::setupActivityChart()
{
    QChart *chart = new QChart();
    chart->setTitle("User Activity");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    activityChartView = new QChartView(chart);
    activityChartView->setRenderHint(QPainter::Antialiasing);

    if (ui->stackedWidget->currentWidget()) {
        activityChartView->setParent(ui->stackedWidget->currentWidget());
        activityChartView->setGeometry(QRect(660, 20, 250, 200));
    }

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(activityChartView);
    shadow->setBlurRadius(15);
    shadow->setOffset(4, 4);
    shadow->setColor(QColor(0, 0, 0, 80));
    activityChartView->setGraphicsEffect(shadow);

    updateActivityChart();
    activityChartView->show();
}

void home::updateActivityChart()
{
    if (!activityChartView || !activityChartView->chart())
        return;

    QChart *chart = activityChartView->chart();
    chart->removeAllSeries();

    QMap<QString, int> activityData = collectActivityData();

    if (activityData.size() <= 5) {
        QPieSeries *series = new QPieSeries();
        series->setHoleSize(0.35);
        for (auto it = activityData.begin(); it != activityData.end(); ++it) {
            QPieSlice *slice = series->append(it.key(), it.value());
            slice->setLabelVisible(true);
            if (it.key().contains("Added", Qt::CaseInsensitive))
                slice->setColor(QColor(76, 175, 80));
            else if (it.key().contains("Deleted", Qt::CaseInsensitive))
                slice->setColor(QColor(244, 67, 54));
            else if (it.key().contains("Edited", Qt::CaseInsensitive))
                slice->setColor(QColor(33, 150, 243));
            else if (it.key().contains("Exported", Qt::CaseInsensitive))
                slice->setColor(QColor(156, 39, 176));
            else
                slice->setColor(QColor(255, 193, 7));
        }
        chart->addSeries(series);
        chart->setTitle("Activity Distribution");
    } else {
        QBarSeries *series = new QBarSeries();
        QBarSet *set = new QBarSet("Count");
        QStringList categories;
        for (auto it = activityData.begin(); it != activityData.end(); ++it) {
            *set << it.value();
            categories << it.key();
        }
        series->append(set);
        chart->addSeries(series);

        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0, set->at(set->count() - 1) + 1);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        chart->setTitle("Activity Count by Type");
    }
    chart->update();
}

QMap<QString, int> home::collectActivityData()
{
    QMap<QString, int> activityData;
    for (int i = 0; i < ui->activityLogList->count(); i++) {
        QString logEntry = ui->activityLogList->item(i)->text();
        int colonPos = logEntry.indexOf(':');
        if (colonPos != -1 && colonPos + 2 < logEntry.length()) {
            QString entry = logEntry.mid(colonPos + 2);
            QString category;
            if (entry.contains("Added user"))
                category = "Added user";
            else if (entry.contains("Deleted user"))
                category = "Deleted user";
            else if (entry.contains("Edited user"))
                category = "Edited user";
            else if (entry.contains("Changed status"))
                category = "Status change";
            else if (entry.contains("Exported PDF"))
                category = "Exported PDF";
            else if (entry.contains("Searched for"))
                category = "Search";
            else if (entry.contains("Loaded"))
                category = "Data load";
            else
                category = "Other action";
            activityData[category] = activityData.value(category, 0) + 1;
        }
    }
    return activityData;
}

// ----- User Status Chart -----

void home::setupUserStatusChart()
{
    userStatusChartWidget = new QWidget(ui->stackedWidget->currentWidget());
    userStatusChartWidget->setGeometry(QRect(660, 240, 510, 300));

    QVBoxLayout *layout = new QVBoxLayout(userStatusChartWidget);
    layout->setContentsMargins(10, 10, 10, 10);

    QChart *chart = new QChart();
    chart->setTitle("User Status Distribution");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    int onlineCount = ui->nbr_online->text().toInt();
    int offlineCount = ui->nbr_offline->text().toInt();

    QPieSeries *series = new QPieSeries();
    QPieSlice *onlineSlice = series->append(QString("Online (%1)").arg(onlineCount), onlineCount);
    QPieSlice *offlineSlice = series->append(QString("Offline (%1)").arg(offlineCount), offlineCount);

    onlineSlice->setBrush(QColor(76, 175, 80));
    offlineSlice->setBrush(QColor(244, 67, 54));

    onlineSlice->setExploded(true);
    onlineSlice->setExplodeDistanceFactor(0.1);
    offlineSlice->setExploded(true);
    offlineSlice->setExplodeDistanceFactor(0.1);

    onlineSlice->setLabelVisible(true);
    offlineSlice->setLabelVisible(true);

    series->setLabelsVisible(true);
    series->setLabelsPosition(QPieSlice::LabelOutside);

    chart->addSeries(series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(chartView);
    userStatusChartWidget->setLayout(layout);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(userStatusChartWidget);
    shadow->setBlurRadius(10);
    shadow->setOffset(3, 3);
    shadow->setColor(QColor(0, 0, 0, 60));
    userStatusChartWidget->setGraphicsEffect(shadow);

    userStatusHistory[QDateTime::currentDateTime()] = qMakePair(onlineCount, offlineCount);

    userStatusChartWidget->show();
}

void home::updateUserStatusChart()
{
    if (!userStatusChartWidget) return;

    QChartView *chartView = userStatusChartWidget->findChild<QChartView*>();
    if (!chartView || !chartView->chart()) return;

    QChart *chart = chartView->chart();
    chart->removeAllSeries();

    // Remove all axes
    QList<QAbstractAxis*> axes = chart->axes();
    for (QAbstractAxis* axis : axes) {
        chart->removeAxis(axis);
        delete axis;
    }

    int onlineCount = ui->nbr_online->text().toInt();
    int offlineCount = ui->nbr_offline->text().toInt();

    // Create bar sets
    QBarSet *onlineSet = new QBarSet("Online");
    QBarSet *offlineSet = new QBarSet("Offline");

    onlineSet->setColor(QColor(76, 175, 80));
    offlineSet->setColor(QColor(244, 67, 54));

    *onlineSet << onlineCount;
    *offlineSet << offlineCount;

    QBarSeries *series = new QBarSeries();
    series->append(onlineSet);
    series->append(offlineSet);

    series->setLabelsVisible(true);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    series->setLabelsFormat("@value");

    chart->addSeries(series);

    QStringList categories;
    categories << "User Status";

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setGridLineVisible(false);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    int maxCount = qMax(onlineCount, offlineCount);
    maxCount = qMax(maxCount, 1);
    axisY->setRange(0, maxCount + 1);
    axisY->setLabelFormat("%d");
    axisY->setTitleText("Count");
    axisY->setGridLineVisible(true);
    axisY->setMinorGridLineVisible(false);
    axisY->setTickCount(maxCount + 2);
    axisY->setMinorTickCount(0);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    userStatusHistory[QDateTime::currentDateTime()] = qMakePair(onlineCount, offlineCount);
    chart->update();
}

void home::recordUserStatusSnapshot()
{
    int onlineCount = ui->nbr_online->text().toInt();
    int offlineCount = ui->nbr_offline->text().toInt();
    userStatusHistory[QDateTime::currentDateTime()] = qMakePair(onlineCount, offlineCount);

    while (userStatusHistory.size() > 50) {
        userStatusHistory.remove(userStatusHistory.keys().first());
    }
    updateUserStatusChart();
}
