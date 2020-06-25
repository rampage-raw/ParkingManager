#ifndef EDIT_INFO_H
#define EDIT_INFO_H

#include <QWidget>
#include <QMessageBox>
namespace Ui {
class edit_info;
}

class edit_info : public QWidget
{
    Q_OBJECT

public:
    explicit edit_info(QWidget *parent = nullptr);
    ~edit_info();
    void emit_user_updateinfo();
signals:
    void send_user_updateinfo(QString, QString, QString, QString);
private:
    Ui::edit_info *ui;
};

#endif // EDIT_INFO_H
