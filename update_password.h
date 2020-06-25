#ifndef UPDATE_PASSWORD_H
#define UPDATE_PASSWORD_H

#include <QWidget>
#include <QMessageBox>
namespace Ui {
class update_password;
}

class update_password : public QWidget
{
    Q_OBJECT

public:
    explicit update_password(QWidget *parent = nullptr);
    ~update_password();
    void dealpass();
signals:
    void sendpassword(QString, QString);
private:
    Ui::update_password *ui;
};

#endif // UPDATE_PASSWORD_H
