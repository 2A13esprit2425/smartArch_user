/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QWidget *centralwidget;
    QLabel *label_2;
    QLineEdit *pass;
    QPushButton *loginbtn;
    QPushButton *hwidbtn;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QCheckBox *checkBox;
    QPushButton *signup;

    void setupUi(QMainWindow *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName("login");
        login->resize(506, 515);
        login->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"   "));
        centralwidget = new QWidget(login);
        centralwidget->setObjectName("centralwidget");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(220, 270, 71, 16));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        pass = new QLineEdit(centralwidget);
        pass->setObjectName("pass");
        pass->setGeometry(QRect(200, 310, 113, 24));
        pass->setStyleSheet(QString::fromUtf8("background-color:#4A90E2;"));
        pass->setEchoMode(QLineEdit::EchoMode::Password);
        loginbtn = new QPushButton(centralwidget);
        loginbtn->setObjectName("loginbtn");
        loginbtn->setGeometry(QRect(180, 410, 80, 24));
        loginbtn->setStyleSheet(QString::fromUtf8("background-color:#4A90E2;"));
        hwidbtn = new QPushButton(centralwidget);
        hwidbtn->setObjectName("hwidbtn");
        hwidbtn->setGeometry(QRect(60, 230, 411, 24));
        hwidbtn->setStyleSheet(QString::fromUtf8("background-color:#4A90E2;"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 40, 491, 151));
        label_3->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/logo1.png);"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(-100, -90, 251, 201));
        label_4->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/823.jpg);"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(370, -80, 251, 201));
        label_5->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/823.jpg);"));
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(280, 410, 121, 22));
        checkBox->setStyleSheet(QString::fromUtf8("color:black"));
        signup = new QPushButton(centralwidget);
        signup->setObjectName("signup");
        signup->setGeometry(QRect(390, 460, 80, 24));
        signup->setStyleSheet(QString::fromUtf8("background-color:#4A90E2;"));
        login->setCentralWidget(centralwidget);

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QMainWindow *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "login", nullptr));
        label_2->setText(QCoreApplication::translate("login", "Password", nullptr));
        loginbtn->setText(QCoreApplication::translate("login", "AUTH", nullptr));
        hwidbtn->setText(QString());
        label_3->setText(QString());
        label_4->setText(QString());
        label_5->setText(QString());
        checkBox->setText(QCoreApplication::translate("login", "Remember me", nullptr));
        signup->setText(QCoreApplication::translate("login", "SIGN UP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
