#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>
#include <record.h>
#include <edit_info.h>
#include <topup.h>
#include <update_password.h>
#include <QMessageBox>
#include <QGridLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSql>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariantList>
#include <QDebug>
#include <QLayout>
#include <QLayoutItem>
#include <QTimer>
#include <qdatetime.h>
namespace Ui {
class userwindow;
}

class userwindow : public QWidget
{
    Q_OBJECT

public:
    explicit userwindow(QWidget *parent = nullptr);
    ~userwindow();
    void editinfo();
    void inqrec();
    void top_up();
    void updatepassword();
    void emitquit();
    void emitprint();
    void print(QString data[][3], int arr[], int len);
    void printinfo(QString, QString, QString, QString, QString, QString, int);
    void emit_main_updateinfo(QString, QString, QString, QString);
    void emit_main_updatepass(QString, QString);
    void emit_main_balance(int);
    void emit_main_yearmember();
    void emit_main_monthmember();
    void emit_main_payment();
    void emit_main_consumption();
    void timerUpdate();
    void reservation();
    void setpayment(int, int);
    void recordprint(QString str[][2], int num[][4], QDateTime time[][2], int len);
signals:
    void sendquit();
    void sendprint();
    void send_main_updateinfo(QString, QString, QString, QString);
    void send_main_updatepass(QString, QString);
    void send_main_balance(int);
    void send_main_yearmember();
    void send_main_monthmember();
    void send_main_reservation(QString, int, QDateTime, QDateTime);
    void send_main_payment(int, int);
    void send_main_consumption();
private:
    Ui::userwindow *ui;
    edit_info personalinfo;
    record expenses;
    topup topupinfo;
    update_password updatepass;
    QGridLayout *pLayout;
};

#endif // USERWINDOW_H
