#include "registered.h"
#include "ui_registered.h"

registered::registered(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registered)
{
    ui->setupUi(this);

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);

    ui->label->setPalette(pe);
    ui->label_3->setPalette(pe);
    ui->label_4->setPalette(pe);
    ui->label_5->setPalette(pe);
    ui->label_6->setPalette(pe);
    ui->label_7->setPalette(pe);
    ui->label_8->setPalette(pe);
    ui->label_9->setPalette(pe);

    ui->pushButton->setPalette(pe);

    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);

    QPixmap pixmap = QPixmap(":/ground_2.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

    connect(ui->pushButton, &QPushButton::clicked, this, &registered::registing);
}

void registered::registing(){
    QString id = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    QString repassword = ui->lineEdit_3->text();
    QString name = ui->lineEdit_4->text();
    QString carid = ui->lineEdit_5->text();
    QString cartype = ui->comboBox->currentText();
    QString tel = ui->lineEdit_6->text();
    if(id.isEmpty() || password.isEmpty() || repassword.isEmpty() || name.isEmpty() || carid.isEmpty() || tel.isEmpty()){
        QMessageBox::warning(nullptr, QStringLiteral("错误"), QStringLiteral("输入的信息不完整"), QMessageBox::Yes);
    }
    else if(password != repassword){
        QMessageBox::warning(nullptr, QStringLiteral("错误"), QStringLiteral("两次输入的密码不相同"), QMessageBox::Yes);
    }
    else{
        emit(sendregist(id, password, name, carid, cartype, tel));

    }
}

registered::~registered()
{
    delete ui;
}
