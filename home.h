#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QSqlDatabase>
#include <QList>
#include <QVariantMap>
#include <QEvent>
#include <QMap>
#include <QDateTime>
#include <QPair>
#include <QTableWidgetItem>

// Include Qt Charts headers
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>

// Do not use a namespace prefix here because your Qt version does not define one.

namespace Ui {
class home;
}

class home : public QWidget
{
    Q_OBJECT

public:
    explicit home(QWidget *parent = nullptr);
    ~home();

private:
    Ui::home *ui;
    QSqlDatabase db;

    // Chart-related members – using types directly without a namespace prefix
    QChartView *activityChartView;
    QWidget *userStatusChartWidget;
    QMap<QDateTime, QPair<int, int>> userStatusHistory;

    bool connectToDatabase();
    void applyShadowEffect();
    void logActivity(const QString &activity);
    void startDatabaseLoading();
    void updateEmployeeTable(const QList<QVariantMap> &records);
    void updateCurrentUserStatus(const QString &status);
    void updateUserCounts();

    // Chart-related methods
    void setupActivityChart();
    void updateActivityChart();
    QMap<QString, int> collectActivityData();
    void setupUserStatusChart();
    void updateUserStatusChart();
    void recordUserStatusSnapshot();

    void updateWhitelistTable();


private slots:
    void onTableHeaderSectionClicked(int index);
    void on_pushButton_4_clicked(); // Close window
    void on_pushButton_5_clicked(); // Minimize window
    void on_pushButton_2_clicked(); // Search button
    void on_pushButton_3_clicked(); // Add employee button
    void handleEditButton();
    void handleDeleteButton();
    void handleStatusToggle(int row, int column);
    void on_save_clicked();         // Select PDF save path
    void exportPdf();
    void on_whitelist_user_clicked();
    void onWhitelistItemChanged(QTableWidgetItem *item);

protected:
    void changeEvent(QEvent *event) override;
};

#endif // HOME_H
