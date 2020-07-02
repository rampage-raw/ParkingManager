#include "update_password.h"
#include "ui_update_password.h"

update_password::update_password(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::update_password)
{
    ui->setupUi(this);

    QPixmap pixmap = QPixmap(":/timg.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

    connect(ui->pushButton, &QPushButton::clicked, this, &update_password::dealpass);
}

void update_password::dealpass(){
    QString oldpass = ui->lineEdit->text();
    QString newpass = ui->lineEdit_2->text();
    QString renewpass = ui->lineEdit_3->text();
    if(oldpass.isEmpty() || newpass.isEmpty() || renewpass.isEmpty()){
        QMessageBox::warning(nullptr, QStringLiteral("错误"), QStringLiteral("输入的密码不能为空"), QMessageBox::Yes);
    }
    else{
        if(newpass != renewpass){
            QMessageBox::warning(nullptr, QStringLiteral("错误"), QStringLiteral("两次输入的密码不一致"), QMessageBox::Yes);
        }
        else{
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            emit(sendpassword(oldpass, newpass));
        }
    }

}

update_password::~update_password()
{
    delete ui;
}
