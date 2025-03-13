#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QSqlDatabase>

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_registerbtn_clicked();
    void on_hwidbtn_clicked();

private:
    Ui::Register *ui;
    QSqlDatabase db;

    bool connectToDatabase();
    QString getHwid();
    QString convertHwidToFriendlyId(const QString &hwid);
};

#endif // REGISTER_H
