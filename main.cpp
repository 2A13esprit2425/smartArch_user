#include <QApplication>
#include "login.h"
#include "home.h"

int main(int argc, char *argv[]) {
    qputenv("QT_DEBUG_PLUGINS", QByteArray("1"));

    QApplication a(argc, argv);

    login loginWindow;
    home w;
    qDebug() << "Available SQL drivers:" << QSqlDatabase::drivers();

    qApp->setStyleSheet("QMessageBox QLabel { color: black; }");
    loginWindow.show();
    return a.exec();
}
