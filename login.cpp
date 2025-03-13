#include "login.h"
#include "ui_login.h"
#include "register.h"
#include "home.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSettings>
#include <QCryptographicHash>
#include <QClipboard>
#include <QGuiApplication>
#include <QDebug>

#ifdef __MINGW32__
#define __CPUIDEX_DEFINED
#endif
#include <windows.h>
#include <intrin.h>
#include <sstream>

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);

    QString t = "PLANOVA 1.0.0 Beta AUTH";
    this->setWindowTitle(t);

    if (!connectToDatabase()) {
        QMessageBox::critical(this, "Database Error", "Failed to connect to the database.");
    }

    // Generate HWID and display it on the HWID button
    QString hwid = getHwid();
    ui->hwidbtn->setText(hwid);

    loadRememberedCredentials();
}

login::~login()
{
    delete ui;
}

bool login::connectToDatabase()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Oracle in XE};DBQ=XE;UID=DALI;PWD=dali;");
    if (!db.open()) {
        qDebug() << "Database connection error:" << db.lastError().text();
        return false;
    }
    return true;
}

void login::loadRememberedCredentials()
{
    QSettings settings("Archiflow", "Archiflow");

    bool remember = settings.value("rememberMe", false).toBool();
    if (remember) {
        QString savedUser = settings.value("userId", "").toString();
        QString savedPass = settings.value("password", "").toString();

        // Optionally display or use the saved userId as needed.
        ui->pass->setText(savedPass);
        ui->checkBox->setChecked(true);
    }
}

void login::saveRememberedCredentials(const QString &userId, const QString &plainPassword)
{
    QSettings settings("Archiflow", "Archiflow");
    settings.setValue("rememberMe", true);
    settings.setValue("userId", userId);
    settings.setValue("password", plainPassword);
}

void login::clearRememberedCredentials()
{
    QSettings settings("Archiflow", "Archiflow");
    settings.remove("rememberMe");
    settings.remove("userId");
    settings.remove("password");
}

// --- Static functions ---

QString login::getHwid()
{
    std::stringstream ss;

    // BIOS
    {
        char biosSerial[256] = {0};
        DWORD size = sizeof(biosSerial);
        if (GetSystemFirmwareTable('RSMB', 0, biosSerial, size)) {
            ss << "BIOS: " << biosSerial << "\n";
        } else {
            ss << "BIOS: Error retrieving BIOS serial\n";
        }
    }

    // Motherboard
    {
        char boardSerial[256] = {0};
        DWORD size = sizeof(boardSerial);
        if (GetSystemFirmwareTable('RSMB', 0, boardSerial, size)) {
            ss << "Board: " << boardSerial << "\n";
        } else {
            ss << "Board: Error retrieving motherboard serial\n";
        }
    }

    // CPU
    {
        int cpuInfo[4];
        __cpuid(cpuInfo, 0);
        ss << "CPU: " << std::hex << cpuInfo[1] << cpuInfo[3] << cpuInfo[2] << "\n";
    }

    // Disk
    {
        char diskSerial[256] = {0};
        DWORD sz = sizeof(diskSerial);
        HANDLE hDisk = CreateFileA("\\\\.\\PHYSICALDRIVE0",
                                   GENERIC_READ,
                                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                                   NULL,
                                   OPEN_EXISTING, 0, NULL);
        if (hDisk != INVALID_HANDLE_VALUE) {
            DWORD bytesReturned;
            if (DeviceIoControl(hDisk,
                                IOCTL_STORAGE_QUERY_PROPERTY,
                                NULL,
                                0,
                                diskSerial,
                                sz,
                                &bytesReturned,
                                NULL))
            {
                ss << "Disk: " << diskSerial << "\n";
            } else {
                ss << "Disk: Error retrieving disk serial\n";
            }
            CloseHandle(hDisk);
        } else {
            ss << "Disk: Error opening physical drive\n";
        }
    }

    QString combined = QString::fromStdString(ss.str()) + "C:\\Windows\\SysWOW64\\ntdll.dll";
    QString hwid = QString(QCryptographicHash::hash(combined.toUtf8(), QCryptographicHash::Sha256).toHex());
    return hwid;
}

QString login::convertHwidToFriendlyId(const QString &hwid)
{
    QString friendly = hwid;
    std::reverse(friendly.begin(), friendly.end());
    if (friendly.length() > 10) {
        friendly = friendly.left(10);
    }
    return friendly;
}

void login::on_hwidbtn_clicked()
{
    QString hwid = getHwid();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(hwid);

    QMessageBox::information(this, "Copied", "HWID copied to clipboard!");
}

void login::on_loginbtn_clicked()
{
    // Generate HWID and compute friendly ID (same as registration)
    QString hwid = getHwid();
    QString userId = convertHwidToFriendlyId(hwid);  // Use exactly the same steps as registration

    QString pass = ui->pass->text();

    // Log computed values for debugging
    qDebug() << "Computed HWID:" << hwid;
    qDebug() << "Friendly HWID (userId):" << userId;
    qDebug() << "Entered password:" << pass;

    // Hash the entered password
    QByteArray hashedInput = QCryptographicHash::hash(pass.toUtf8(), QCryptographicHash::Sha256).toHex();
    qDebug() << "Hashed password:" << QString(hashedInput);

    if (userId.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "HWID and password must be provided.");
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT password_hash FROM empl WHERE user_id = :userId");
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "SQL error:" << query.lastError().text();
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    if (query.next()) {
        QString storedHash = query.value(0).toString();
        qDebug() << "Stored password hash:" << storedHash;
        if (storedHash == QString(hashedInput)) {
            if (ui->checkBox->isChecked()) {
                saveRememberedCredentials(userId, pass);
            } else {
                clearRememberedCredentials();
            }
            home *homeWindow = new home();
            homeWindow->show();
            this->hide();
        } else {
            qDebug() << "Hash mismatch: entered" << QString(hashedInput)
            << "vs stored" << storedHash;
            QMessageBox::warning(this, "Login Failed", "Invalid HWID or password.");
        }
    } else {
        qDebug() << "No record found for userId:" << userId;
        QMessageBox::warning(this, "Login Failed", "Invalid HWID or password.");
    }
}

void login::on_signup_clicked()
{
    Register *regWindow = new Register();
    regWindow->show();
}
