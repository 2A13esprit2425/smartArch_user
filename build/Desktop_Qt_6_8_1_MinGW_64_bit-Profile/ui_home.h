/********************************************************************************
** Form generated from reading UI file 'home.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_H
#define UI_HOME_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_home
{
public:
    QFrame *frame;
    QPushButton *pushButton;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QLabel *label_11;
    QStackedWidget *stackedWidget;
    QWidget *page_3;
    QTableWidget *tableWidget;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit_5;
    QComboBox *comboBox;
    QPushButton *pushButton_3;
    QFrame *frame_2;
    QLabel *label_3;
    QLabel *nbr_online;
    QLabel *label_4;
    QLabel *nbr_offline;
    QFrame *frame_4;
    QLineEdit *lineEdit_3;
    QLabel *label_9;
    QLineEdit *lineEdit_6;
    QLabel *label_12;
    QLabel *label_13;
    QListWidget *activityLogList;
    QPushButton *exportpdf;
    QLineEdit *pathtosave;
    QPushButton *save;
    QLabel *label_10;
    QLabel *label_7;
    QRadioButton *radioButton1compressionon;
    QRadioButton *radioButton2compressionoff;
    QLabel *label_2;
    QLabel *time;
    QTableWidget *whitelist_table;
    QFrame *frame_5;
    QLineEdit *hwid;
    QLabel *label_21;
    QLabel *label_22;
    QPushButton *whitelist_user;
    QFrame *frame_3;
    QLabel *label_5;
    QLabel *label;
    QWidget *widget;
    QFrame *line;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;

    void setupUi(QWidget *home)
    {
        if (home->objectName().isEmpty())
            home->setObjectName("home");
        home->resize(1465, 799);
        home->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 247, 250);"));
        frame = new QFrame(home);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 201, 801));
        frame->setStyleSheet(QString::fromUtf8("background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, \n"
"stop:0 #4A90E2, stop:1 #6A5ACD); /* Gradient from Blue to Purple */"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 180, 211, 121));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        pushButton->setFont(font);
        pushButton->setFlat(true);
        pushButton_8 = new QPushButton(frame);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(0, 300, 211, 121));
        pushButton_8->setFont(font);
        pushButton_8->setFlat(true);
        pushButton_9 = new QPushButton(frame);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(0, 430, 211, 121));
        pushButton_9->setFont(font);
        pushButton_9->setFlat(true);
        pushButton_10 = new QPushButton(frame);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(0, 550, 211, 121));
        pushButton_10->setFont(font);
        pushButton_10->setFlat(true);
        label_11 = new QLabel(frame);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(0, 20, 221, 161));
        label_11->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/logo.png);"));
        stackedWidget = new QStackedWidget(home);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(220, 50, 1211, 731));
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        tableWidget = new QTableWidget(page_3);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        if (tableWidget->rowCount() < 5)
            tableWidget->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setItem(0, 4, __qtablewidgetitem10);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(40, 320, 601, 221));
        tableWidget->setFont(font);
        tableWidget->setStyleSheet(QString::fromUtf8("/* Style the header sections */\n"
"QHeaderView::section {\n"
"    color: white; /* Text Color for headers */\n"
"    background-color: #4A90E2; /* Background Color for headers */\n"
"    font-weight: bold; /* Make header text bold */\n"
"    font-size: 14px;\n"
"    padding: 5px;\n"
"}\n"
"/* Style the table items */\n"
"QTableWidget::item {\n"
"    color: black; /* Ensure text color is black */\n"
"}\n"
"\n"
"/* Ensure disabled items also appear black */\n"
"QTableWidget::item:disabled {\n"
"    color: black;\n"
"    opacity: 1; /* Ensure full opacity */\n"
"}\n"
"\n"
"\n"
"/* Style the table items themselves */\n"
"QTableWidget::item {\n"
"    color: black; /* Text Color for the table items */\n"
"}\n"
""));
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        tableWidget->setAutoScroll(false);
        tableWidget->setTabKeyNavigation(false);
        tableWidget->setDragDropMode(QAbstractItemView::DragDropMode::InternalMove);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(120);
        tableWidget->horizontalHeader()->setHighlightSections(true);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setHighlightSections(true);
        pushButton_2 = new QPushButton(page_3);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(510, 270, 131, 41));
        pushButton_2->setStyleSheet(QString::fromUtf8(" background-color: #4A90E2; /* Background Color */"));
        pushButton_2->setFlat(true);
        lineEdit_5 = new QLineEdit(page_3);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setGeometry(QRect(320, 280, 181, 24));
        lineEdit_5->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"border-bottom-color: rgb(0, 0, 0);\n"
"\n"
"    color: black;  /* Make text color black */\n"
"}"));
        lineEdit_5->setClearButtonEnabled(true);
        comboBox = new QComboBox(page_3);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(180, 280, 121, 24));
        comboBox->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"	color: black;  /* Make text color black */\n"
"\n"
"    border: 2px solid #4A90E2;  /* Blue border */\n"
"    border-radius: 6px;         /* Optional: rounded corners */\n"
"    padding: 5px;\n"
"}\n"
"QComboBox QAbstractItemView {\n"
"    color: black; /* Make dropdown items black */\n"
"    background: white; /* Optional: White background for dropdown */\n"
"    selection-background-color: #4A90E2; /* Blue highlight for selected item */\n"
"    selection-color: white; /* White text when an item is selected */\n"
"}"));
        comboBox->setFrame(false);
        pushButton_3 = new QPushButton(page_3);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(110, 200, 131, 41));
        pushButton_3->setStyleSheet(QString::fromUtf8(" background-color: #4A90E2; /* Background Color */"));
        pushButton_3->setFlat(true);
        frame_2 = new QFrame(page_3);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(920, 20, 251, 201));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 20, 91, 61));
        label_3->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/active-user_9795151.png);"));
        nbr_online = new QLabel(frame_2);
        nbr_online->setObjectName("nbr_online");
        nbr_online->setGeometry(QRect(50, 100, 49, 16));
        nbr_online->setStyleSheet(QString::fromUtf8("color:black"));
        label_4 = new QLabel(frame_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(150, 20, 91, 61));
        label_4->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/imageedit_2_9987478672.png);"));
        nbr_offline = new QLabel(frame_2);
        nbr_offline->setObjectName("nbr_offline");
        nbr_offline->setGeometry(QRect(190, 100, 49, 16));
        nbr_offline->setStyleSheet(QString::fromUtf8("color:black"));
        frame_4 = new QFrame(page_3);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(80, 50, 201, 100));
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        lineEdit_3 = new QLineEdit(frame_4);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(70, 20, 113, 24));
        lineEdit_3->setStyleSheet(QString::fromUtf8("color: black\n"
""));
        label_9 = new QLabel(frame_4);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 20, 49, 16));
        QFont font1;
        font1.setBold(true);
        label_9->setFont(font1);
        label_9->setStyleSheet(QString::fromUtf8("color: black"));
        lineEdit_6 = new QLineEdit(frame_4);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setGeometry(QRect(70, 60, 113, 24));
        lineEdit_6->setStyleSheet(QString::fromUtf8("color: black"));
        label_12 = new QLabel(frame_4);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 100, 49, 16));
        label_12->setFont(font1);
        label_12->setStyleSheet(QString::fromUtf8("color: black"));
        label_13 = new QLabel(frame_4);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 60, 49, 16));
        label_13->setFont(font1);
        label_13->setStyleSheet(QString::fromUtf8("color: black"));
        activityLogList = new QListWidget(page_3);
        new QListWidgetItem(activityLogList);
        activityLogList->setObjectName("activityLogList");
        activityLogList->setGeometry(QRect(660, 550, 511, 151));
        activityLogList->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        exportpdf = new QPushButton(page_3);
        exportpdf->setObjectName("exportpdf");
        exportpdf->setGeometry(QRect(500, 550, 111, 91));
        exportpdf->setStyleSheet(QString::fromUtf8("\n"
"image: url(:/new/prefix1/pdf.png);"));
        pathtosave = new QLineEdit(page_3);
        pathtosave->setObjectName("pathtosave");
        pathtosave->setGeometry(QRect(500, 660, 113, 24));
        pathtosave->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        save = new QPushButton(page_3);
        save->setObjectName("save");
        save->setGeometry(QRect(610, 660, 31, 24));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave));
        save->setIcon(icon);
        label_10 = new QLabel(page_3);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(450, 660, 41, 20));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        label_10->setFont(font2);
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(70, 70, 70);"));
        label_7 = new QLabel(page_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(440, 700, 91, 20));
        label_7->setFont(font2);
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(70, 70, 70);"));
        radioButton1compressionon = new QRadioButton(page_3);
        radioButton1compressionon->setObjectName("radioButton1compressionon");
        radioButton1compressionon->setGeometry(QRect(540, 700, 51, 22));
        radioButton1compressionon->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        radioButton2compressionoff = new QRadioButton(page_3);
        radioButton2compressionoff->setObjectName("radioButton2compressionoff");
        radioButton2compressionoff->setGeometry(QRect(590, 700, 61, 22));
        radioButton2compressionoff->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_2 = new QLabel(page_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(1150, 710, 49, 16));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        time = new QLabel(page_3);
        time->setObjectName("time");
        time->setGeometry(QRect(1100, 710, 41, 16));
        time->setStyleSheet(QString::fromUtf8(" color: black;"));
        whitelist_table = new QTableWidget(page_3);
        if (whitelist_table->columnCount() < 2)
            whitelist_table->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        whitelist_table->setHorizontalHeaderItem(0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        whitelist_table->setHorizontalHeaderItem(1, __qtablewidgetitem12);
        whitelist_table->setObjectName("whitelist_table");
        whitelist_table->setGeometry(QRect(220, 580, 201, 121));
        whitelist_table->setStyleSheet(QString::fromUtf8("/* Style the header sections */\n"
"QHeaderView::section {\n"
"    color: white; /* Text Color for headers */\n"
"    background-color: #4A90E2; /* Background Color for headers */\n"
"    font-weight: bold; /* Make header text bold */\n"
"    font-size: 14px;\n"
"    padding: 5px;\n"
"}\n"
"/* Style the table items */\n"
"QTableWidget::item {\n"
"    color: black; /* Ensure text color is black */\n"
"}\n"
"\n"
"/* Ensure disabled items also appear black */\n"
"QTableWidget::item:disabled {\n"
"    color: black;\n"
"    opacity: 1; /* Ensure full opacity */\n"
"}\n"
"\n"
"\n"
"/* Style the table items themselves */\n"
"QTableWidget::item {\n"
"    color: black; /* Text Color for the table items */\n"
"}\n"
""));
        whitelist_table->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        whitelist_table->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        whitelist_table->setTabKeyNavigation(false);
        whitelist_table->horizontalHeader()->setHighlightSections(true);
        whitelist_table->verticalHeader()->setVisible(false);
        frame_5 = new QFrame(page_3);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(10, 590, 201, 61));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        hwid = new QLineEdit(frame_5);
        hwid->setObjectName("hwid");
        hwid->setGeometry(QRect(70, 20, 113, 24));
        hwid->setStyleSheet(QString::fromUtf8("color: black\n"
""));
        label_21 = new QLabel(frame_5);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(10, 100, 49, 16));
        label_21->setFont(font1);
        label_21->setStyleSheet(QString::fromUtf8("color: black"));
        label_22 = new QLabel(frame_5);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(10, 20, 49, 16));
        label_22->setFont(font1);
        label_22->setStyleSheet(QString::fromUtf8("color: black"));
        whitelist_user = new QPushButton(page_3);
        whitelist_user->setObjectName("whitelist_user");
        whitelist_user->setGeometry(QRect(50, 670, 131, 41));
        whitelist_user->setStyleSheet(QString::fromUtf8(" background-color: #4A90E2; /* Background Color */"));
        whitelist_user->setFlat(true);
        frame_3 = new QFrame(page_3);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(320, 0, 311, 211));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        label_5 = new QLabel(frame_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(130, 170, 49, 16));
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 900 12pt \"Cooper\";"));
        label = new QLabel(frame_3);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 30, 161, 111));
        label->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/userlogo.png);"));
        stackedWidget->addWidget(page_3);
        widget = new QWidget();
        widget->setObjectName("widget");
        stackedWidget->addWidget(widget);
        line = new QFrame(home);
        line->setObjectName("line");
        line->setGeometry(QRect(200, 30, 1261, 20));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        pushButton_4 = new QPushButton(home);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(1399, 0, 61, 34));
        pushButton_4->setFont(font);
        pushButton_4->setStyleSheet(QString::fromUtf8("color:black;"));
        pushButton_4->setFlat(true);
        pushButton_5 = new QPushButton(home);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(1330, 0, 61, 34));
        pushButton_5->setFont(font);
        pushButton_5->setStyleSheet(QString::fromUtf8("color:black;"));
        pushButton_5->setFlat(true);
        stackedWidget->raise();
        frame->raise();
        line->raise();
        pushButton_4->raise();
        pushButton_5->raise();

        retranslateUi(home);

        QMetaObject::connectSlotsByName(home);
    } // setupUi

    void retranslateUi(QWidget *home)
    {
        home->setWindowTitle(QCoreApplication::translate("home", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("home", "Admin Dashboard", nullptr));
        pushButton_8->setText(QCoreApplication::translate("home", "Client Management ", nullptr));
        pushButton_9->setText(QCoreApplication::translate("home", "Project Management", nullptr));
        pushButton_10->setText(QCoreApplication::translate("home", "Resource Management", nullptr));
        label_11->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("home", "User REF	", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("home", "Role", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("home", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("home", "Password", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("home", "Actions\n"
"", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("home", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("home", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("home", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("home", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("home", "New Row", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->item(0, 4);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("home", "Edit/Delete", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        pushButton_2->setText(QCoreApplication::translate("home", "Search", nullptr));
        lineEdit_5->setText(QCoreApplication::translate("home", "Item to Search for ", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("home", "User ID", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("home", "Role", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("home", "Status", nullptr));

        pushButton_3->setText(QCoreApplication::translate("home", "ADD USER", nullptr));
        label_3->setText(QString());
        nbr_online->setText(QCoreApplication::translate("home", "0", nullptr));
        label_4->setText(QString());
        nbr_offline->setText(QCoreApplication::translate("home", "100", nullptr));
        label_9->setText(QCoreApplication::translate("home", "ROLE", nullptr));
        label_12->setText(QCoreApplication::translate("home", "PASS", nullptr));
        label_13->setText(QCoreApplication::translate("home", "PASS", nullptr));

        const bool __sortingEnabled1 = activityLogList->isSortingEnabled();
        activityLogList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = activityLogList->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("home", "Logs...", nullptr));
        activityLogList->setSortingEnabled(__sortingEnabled1);

        exportpdf->setText(QString());
        save->setText(QString());
        label_10->setText(QCoreApplication::translate("home", "Path:", nullptr));
        label_7->setText(QCoreApplication::translate("home", "Compression:", nullptr));
        radioButton1compressionon->setText(QCoreApplication::translate("home", "ON", nullptr));
        radioButton2compressionoff->setText(QCoreApplication::translate("home", "OFF", nullptr));
        label_2->setText(QString());
        time->setText(QCoreApplication::translate("home", "TIME :", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = whitelist_table->horizontalHeaderItem(0);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("home", "HWID", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = whitelist_table->horizontalHeaderItem(1);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("home", "Permission", nullptr));
        label_21->setText(QCoreApplication::translate("home", "PASS", nullptr));
        label_22->setText(QCoreApplication::translate("home", "HWID", nullptr));
        whitelist_user->setText(QCoreApplication::translate("home", "Whitelist User", nullptr));
        label_5->setText(QCoreApplication::translate("home", "DALI", nullptr));
        label->setText(QString());
        pushButton_4->setText(QCoreApplication::translate("home", "X", nullptr));
        pushButton_5->setText(QCoreApplication::translate("home", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class home: public Ui_home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_H
