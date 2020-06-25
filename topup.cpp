#include "topup.h"
#include "ui_topup.h"

topup::topup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::topup)
{
    ui->setupUi(this);

    QPixmap pixmap = QPixmap(":/timg.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

    connect(ui->pushButton, &QPushButton::clicked, this, &topup::emit_user_balance);
}

void topup::emit_user_balance(){
    QString tmp = ui->lineEdit->text();
    if(tmp.isEmpty()){
        QMessageBox::warning(nullptr, QStringLiteral("错误"), QStringLiteral("请输入您需要充值的金额"), QMessageBox::Yes);
    }
    else{
        ui->lineEdit->clear();
        bool ok;
        int balance = tmp.toInt(&ok, 10);
        emit(send_user_balance(balance));
    }

}

topup::~topup()
{
    delete ui;
}
