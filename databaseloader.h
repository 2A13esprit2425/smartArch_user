#ifndef DATABASELOADER_H
#define DATABASELOADER_H

#include <QObject>
#include <QVariantMap>
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class DatabaseLoader : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseLoader(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    void process() {
        // Use a unique connection name for the worker thread
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "WorkerConnection");
        db.setDatabaseName("DRIVER={Oracle in XE};DBQ=XE;UID=DALI;PWD=dali;");
        QList<QVariantMap> records;

        if (!db.open()) {
            emit error(QString("Database connection error: %1")
                           .arg(db.lastError().text()));
            return;
        }

        // Adjust the SELECT columns to match your 'empl' table.
        // For example, here we select user_id, hwid, role, status, password_hash.
        QSqlQuery query(db);
        if (!query.exec("SELECT user_id, hwid, role, status, password_hash FROM empl")) {
            emit error(QString("Database query error: %1")
                           .arg(query.lastError().text()));
            db.close();
            QSqlDatabase::removeDatabase("WorkerConnection");
            return;
        }

        // Read the results into a list of QVariantMaps
        while (query.next()) {
            QVariantMap record;
            record["userId"]       = query.value("user_id");
            record["hwid"]         = query.value("hwid");
            record["role"]         = query.value("role");
            record["status"]       = query.value("status");
            record["password_hash"] = query.value("password_hash");
            records.append(record);
        }

        // Clean up
        db.close();
        QSqlDatabase::removeDatabase("WorkerConnection");

        // Signal that we have finished loading
        emit finished(records);
    }

signals:
    void finished(const QList<QVariantMap> &records);
    void error(const QString &errMsg);
};

#endif // DATABASELOADER_H
