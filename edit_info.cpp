#include "edit_info.h"
#include "ui_edit_info.h"

edit_info::edit_info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edit_info)
{
    ui->setupUi(this);

    QPixmap pixmap = QPixmap(":/timg.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

    connect(ui->pushButton, &QPushButton::clicked, this, &edit_info::emit_user_updateinfo);
}

void edit_info::emit_user_updateinfo(){
    QString name = ui->lineEdit->text();
    QString tel = ui->lineEdit_2->text();
    QString carid = ui->lineEdit_3->text();
    QString cartype = ui->comboBox->currentText();
    if(name.isEmpty() || tel.isEmpty() || carid.isEmpty()){
        QMessageBox::warning(nullptr, QStringLiteral("错误"), QStringLiteral("输入的信息不能为空"), QMessageBox::Yes);
    }
    else{
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        emit(send_user_updateinfo(name, tel, carid, cartype));
    }

}

edit_info::~edit_info()
{
    delete ui;
}
