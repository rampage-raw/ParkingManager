#ifndef TOPUP_H
#define TOPUP_H

#include <QWidget>
#include <QMessageBox>
namespace Ui {
class topup;
}

class topup : public QWidget
{
    Q_OBJECT

public:
    explicit topup(QWidget *parent = nullptr);
    ~topup();
    void emit_user_balance();
signals:
    void send_user_balance(int);
private:
    Ui::topup *ui;
};

#endif // TOPUP_H
