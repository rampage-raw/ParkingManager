#ifndef PARKINGWINDOW_H
#define PARKINGWINDOW_H

#include <QWidget>
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
class parkingwindow;
}

class parkingwindow : public QWidget
{
    Q_OBJECT

public:
    explicit parkingwindow(QWidget *parent = nullptr);
    ~parkingwindow();
    void setline(int, int, int);
    void print(QString parkingstr[], int parkingnum[], QDateTime parkingtim[][2], int len);
private:
    Ui::parkingwindow *ui;
    QGridLayout *pLayout;
};

#endif // PARKINGWINDOW_H
