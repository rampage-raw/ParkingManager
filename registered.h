#ifndef REGISTERED_H
#define REGISTERED_H

#include <QWidget>
#include <QMessageBox>
namespace Ui {
class registered;
}

class registered : public QWidget
{
    Q_OBJECT

public:
    explicit registered(QWidget *parent = nullptr);
    ~registered();
    void registing();
signals:
    void sendregist(QString, QString, QString, QString, QString, QString);
private:
    Ui::registered *ui;
};

#endif // REGISTERED_H
