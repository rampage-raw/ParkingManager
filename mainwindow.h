#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <registered.h>
#include <userwindow.h>
#include <parkingwindow.h>
#include <QSql>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariantList>
#include <QDebug>
#include <QSqlRecord>
#include <QTimer>
#include <qdatetime.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void regist();
    void login();
    void connectmysql();
    void sqlregist(QString, QString, QString, QString, QString, QString);
    void quit();
    void sqlinq();
    void sqlinfo();
    void sqlupdateinfo(QString, QString, QString, QString);
    void sqlupdatepass(QString, QString);
    void sqlupdatebalance(int);
    void sqlyearmember();
    void sqlmonthmember();
    void sqlreservation(QString, int, QDateTime, QDateTime);
    void updatetimeout();
    void sqlpayment(int, int);
    void sqlconsumption();
    void sqlparkinglot();
    void sqlparkingspace();
    QString data[100][3], str[100][2], parkingstr[100];
    int arr[100], num[100][4], parkingnum[100];
    QDateTime tim[100][2], parkingtim[100][2];
    int len, len_2, len_3;

private:
    Ui::MainWindow *ui;
    registered registwindow;
    userwindow user;
    parkingwindow parker;
    QString userid, parkerid;

};

#endif // MAINWINDOW_H
