#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

    // Declare these functions as public static so they can be called without an instance
    static QString getHwid();
    static QString convertHwidToFriendlyId(const QString &hwid);

private slots:
    void on_hwidbtn_clicked();
    void on_loginbtn_clicked();
    void on_signup_clicked();

private:
    Ui::login *ui;
    QSqlDatabase db;

    bool connectToDatabase();
    void loadRememberedCredentials();
    void saveRememberedCredentials(const QString &userId, const QString &plainPassword);
    void clearRememberedCredentials();
};

#endif // LOGIN_H
