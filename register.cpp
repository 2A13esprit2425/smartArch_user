#include "register.h"
#include "ui_register.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>
#include <QClipboard>
#include <QGuiApplication>
#include <windows.h>
#include <intrin.h>
#include <sstream>
#include <algorithm> // for std::reverse

Register::Register(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);

    // Connect to the database
    if (!connectToDatabase()) {
        QMessageBox::critical(this, "Database Error", "Failed to connect to the database.");
    }
}

Register::~Register()
{
    delete ui;
}

bool Register::connectToDatabase()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Oracle in XE};DBQ=XE;UID=DALI;PWD=dali;");
    if (!db.open()) {
        qDebug() << "Database connection error:" << db.lastError().text();
        return false;
    }
    return true;
}

QString Register::getHwid()
{
    std::stringstream ss;
    int cpuInfo[4];
    __cpuid(cpuInfo, 0);
    ss << "CPU: " << std::hex << cpuInfo[1] << cpuInfo[3] << cpuInfo[2] << "\n";

    QString combined = QString::fromStdString(ss.str()) + "C:\\Windows\\SysWOW64\\ntdll.dll";
    QString hwid = QString(
        QCryptographicHash::hash(combined.toUtf8(), QCryptographicHash::Sha256).toHex()
        );
    return hwid;
}

QString Register::convertHwidToFriendlyId(const QString &hwid)
{
    QString friendly = hwid;
    std::reverse(friendly.begin(), friendly.end());
    if (friendly.length() > 10) {
        friendly = friendly.left(10);
    }
    return friendly;
}

void Register::on_hwidbtn_clicked()
{
    QString hwid = getHwid();
    ui->hwidbtn->setText(hwid);

    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(hwid);

    QMessageBox::information(this, "HWID", "HWID generated and copied to clipboard.");
}

void Register::on_registerbtn_clicked()
{
    QString hwidd = ui->hwidbtn->text().trimmed();
    QString hwid = QString(QCryptographicHash::hash(hwidd.toUtf8(), QCryptographicHash::Sha256).toHex());

    qDebug() << "HWID FL CODE:" << hwid;
    QString userRef = convertHwidToFriendlyId(hwid);

    QString role = ui->role->text().trimmed();
    QString pass = ui->pass->text().trimmed();

    if (hwid.isEmpty() || role.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "HWID, Role, and Password must be filled.");
        return;
    }

    QSqlQuery wlQuery(db);
    wlQuery.prepare("SELECT PERMISSION FROM WHITELISTED_USERS WHERE HWID = :hwid");
    wlQuery.bindValue(":hwid", hwid);
    if (!wlQuery.exec()) {
        QMessageBox::critical(this, "Database Error", wlQuery.lastError().text());
        return;
    }

    int permission = wlQuery.value(0).toInt();
    qDebug() << "Whitelist permission:" << permission;

    QString passwordHash = QString(
        QCryptographicHash::hash(pass.toUtf8(), QCryptographicHash::Sha256).toHex()
        );

    // 6. Check if this userRef already exists in the database.
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
        QMessageBox::warning(this, "Register", "A user with this ID (derived from HWID) already exists.");
        return;
    }

    // 7. Insert into 'empl'
    QString status = "Offline";
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

    QMessageBox::information(this, "Register", "User registered successfully!");

    // Clear fields
    ui->role->clear();
    ui->pass->clear();
    ui->hwidbtn->setText("");
}
