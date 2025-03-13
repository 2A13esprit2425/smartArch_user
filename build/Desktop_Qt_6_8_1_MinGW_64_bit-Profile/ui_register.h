/********************************************************************************
** Form generated from reading UI file 'register.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QPushButton *registerbtn;
    QLabel *label_2;
    QPushButton *hwidbtn;
    QLineEdit *role;
    QLabel *label_5;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_6;
    QLineEdit *pass;
    QLabel *label_7;

    void setupUi(QWidget *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName("Register");
        Register->resize(506, 515);
        Register->setStyleSheet(QString::fromUtf8("background-color:  rgb(255, 255, 255);"));
        registerbtn = new QPushButton(Register);
        registerbtn->setObjectName("registerbtn");
        registerbtn->setGeometry(QRect(180, 380, 171, 24));
        registerbtn->setStyleSheet(QString::fromUtf8("background-color:#4A90E2;"));
        label_2 = new QLabel(Register);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 240, 71, 16));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        hwidbtn = new QPushButton(Register);
        hwidbtn->setObjectName("hwidbtn");
        hwidbtn->setGeometry(QRect(210, 320, 111, 24));
        hwidbtn->setStyleSheet(QString::fromUtf8("background-color:#4A90E2;"));
        role = new QLineEdit(Register);
        role->setObjectName("role");
        role->setGeometry(QRect(210, 240, 113, 24));
        role->setStyleSheet(QString::fromUtf8("background-color:#4A90E2;"));
        role->setEchoMode(QLineEdit::EchoMode::Normal);
        label_5 = new QLabel(Register);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(370, -60, 251, 201));
        label_5->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/823.jpg);"));
        label_4 = new QLabel(Register);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(-100, -70, 251, 201));
        label_4->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/823.jpg);"));
        label_3 = new QLabel(Register);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 60, 491, 151));
        label_3->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/logo1.png);"));
        label_6 = new QLabel(Register);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(130, 280, 49, 16));
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        pass = new QLineEdit(Register);
        pass->setObjectName("pass");
        pass->setGeometry(QRect(210, 280, 113, 24));
        pass->setStyleSheet(QString::fromUtf8("background-color:#4A90E2;"));
        pass->setEchoMode(QLineEdit::EchoMode::Normal);
        label_7 = new QLabel(Register);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(130, 320, 49, 16));
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_3->raise();
        registerbtn->raise();
        label_2->raise();
        hwidbtn->raise();
        role->raise();
        label_5->raise();
        label_4->raise();
        label_6->raise();
        pass->raise();
        label_7->raise();

        retranslateUi(Register);

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QWidget *Register)
    {
        Register->setWindowTitle(QCoreApplication::translate("Register", "Form", nullptr));
        registerbtn->setText(QCoreApplication::translate("Register", "REGISTER", nullptr));
        label_2->setText(QCoreApplication::translate("Register", "ROLE", nullptr));
        hwidbtn->setText(QString());
        label_5->setText(QString());
        label_4->setText(QString());
        label_3->setText(QString());
        label_6->setText(QCoreApplication::translate("Register", "PASS", nullptr));
        label_7->setText(QCoreApplication::translate("Register", "HWID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
