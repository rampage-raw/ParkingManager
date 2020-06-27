#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QLabel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectmysql();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updatetimeout);
    timer->start(1000);

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);

    ui->label->setPalette(pe);
    ui->label_3->setPalette(pe);
    ui->label_4->setPalette(pe);
    ui->label_5->setPalette(pe);

    ui->groupBox->setPalette(pe);
    ui->pushButton->setPalette(pe);
    ui->pushButton_2->setPalette(pe);

    ui->lineEdit_2->setEchoMode(QLineEdit::Password);

    QPixmap pixmap = QPixmap(":/ground.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::regist);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::login);
    connect(&registwindow, &registered::sendregist, this, &MainWindow::sqlregist);
    connect(&user, &userwindow::sendquit, this, &MainWindow::quit);
    connect(&user, &userwindow::sendprint, this, &MainWindow::sqlinq);
    connect(&user, &userwindow::send_main_updateinfo, this, &MainWindow::sqlupdateinfo);
    connect(&user, &userwindow::send_main_updatepass, this, &MainWindow::sqlupdatepass);
    connect(&user, &userwindow::send_main_balance, this, &MainWindow::sqlupdatebalance);
    connect(&user, &userwindow::send_main_yearmember, this, &MainWindow::sqlyearmember);
    connect(&user, &userwindow::send_main_monthmember, this, &MainWindow::sqlmonthmember);
    connect(&user, &userwindow::send_main_reservation, this, &MainWindow::sqlreservation);
    connect(&user, &userwindow::send_main_payment, this, &MainWindow::sqlpayment);
    connect(&user, &userwindow::send_main_consumption, this, &MainWindow::sqlconsumption);
}

void MainWindow::connectmysql()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("parking");
    if (!db.open())
    {
        QMessageBox::warning(this, "错误", db.lastError().text());
        return;
    }
    QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("数据库成功连接！"), QMessageBox::Yes);
    /*
    QSqlQuery query_2;
    query_2.exec("select * from stu");
    while(query_2.next())
    {
        qDebug() << query_2.value(0).toString() << endl;
    }
    */

    return;
}

void MainWindow::regist(){
    registwindow.show();
}

void MainWindow::login(){
    QString account = this->ui->lineEdit->text();
    QString password = this->ui->lineEdit_2->text();
    if(account.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(nullptr, QStringLiteral("错误"), QStringLiteral("账号密码不能为空"), QMessageBox::Yes);
    }
    else{
        if(!ui->radioButton->isChecked() && !ui->radioButton_2->isChecked())
        {
            QMessageBox::warning(nullptr, QStringLiteral("警告"), QStringLiteral("请选择你的身份"), QMessageBox::Yes);
        }
        else if(ui->radioButton_2->isChecked())
        {
            QSqlQuery query;
            QString rightword;
            QString str = QString("select password from userinfo where id = '%1'").arg(account);
            query.exec(str);
            while(query.next())
            {
                rightword = query.value(0).toString();
            }
//            qDebug() << rightword << endl;
            if(password == rightword){
                userid = account;
                this->hide();
                this->sqlinq();
                this->sqlinfo();
                user.show();
                ui->lineEdit->clear();
                ui->lineEdit_2->clear();
            }
            else{
                QMessageBox::warning(nullptr, QStringLiteral("错误"), QStringLiteral("账号密码错误"), QMessageBox::Yes);
                ui->lineEdit->clear();
                ui->lineEdit_2->clear();
            }
        }
        else {
            QSqlQuery query;
            QString rightword;
            QString str = QString("select parkingpassword from parkinglot where parkingid = '%1'").arg(account);
            query.exec(str);
            while(query.next())
            {
                rightword = query.value(0).toString();
            }
            if(password == rightword){
                parkerid = account;
                this->sqlparkinglot();
                this->sqlparkingspace();
                parker.show();
                this->hide();
                ui->lineEdit->clear();
                ui->lineEdit_2->clear();
            }
            else{
                QMessageBox::warning(nullptr, QStringLiteral("错误"), QStringLiteral("账号密码错误"), QMessageBox::Yes);
                ui->lineEdit->clear();
                ui->lineEdit_2->clear();
            }
        }
    }

}

void MainWindow::sqlregist(QString id, QString password, QString name, QString carid, QString cartype, QString tel){
    QSqlQuery query;
    QString str = QString("insert into userinfo(id,name,tel,type,balance,password) values('%1', '%2', '%3', '普通用户', 0, '%4')").arg(id).arg(name).arg(tel).arg(password);
    QString str_2 = QString("insert into carinfo(id,carid,cartype) values('%1', '%2', '%3')").arg(id).arg(carid).arg(cartype);
    if(query.exec(str) && query.exec(str_2)){
        QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("注册成功！"), QMessageBox::Yes);
    }
    else{
        QMessageBox::warning(nullptr, QStringLiteral("错误"), QStringLiteral("该用户名已被注册"), QMessageBox::Yes);
    }
}

void MainWindow::sqlinq(){
//    qDebug() << "deal" << endl;
    QSqlQuery query;
    QString inquire = QString("select * from parkingspace where situation = '空闲'");
    query.exec(inquire);
    int i = 0;
    while(query.next()){
        data[i][0] = query.value(2).toString();
        data[i][1] = query.value(3).toString();
        data[i][2] = query.value(1).toString();
        arr[i] = query.value(0).toInt();
//        qDebug() << arr[i] << ' ' << data[i][0] << ' ' << data[i][1] << ' ' << data[i][2] << endl;
        i++;
    }
    len = i;
//    qDebug() << len << endl;
    user.print(data, arr, len);
}

void MainWindow::sqlinfo(){
    QString name, carid, tel, cartype, type;
    int balance = 0;
    QSqlQuery query;
    QString inquire = QString("select * from userinfo where id = '%1'").arg(userid);
    query.exec(inquire);
    while(query.next()){
        name = query.value(1).toString();
        tel = query.value(2).toString();
        type = query.value(3).toString();
        balance = query.value(4).toInt();
    }
    QString inquire_2 = QString("select * from carinfo where id = '%1'").arg(userid);
    query.exec(inquire_2);
    while(query.next()){
        carid = query.value(1).toString();
        cartype = query.value(2).toString();
    }
    user.printinfo(userid, name, carid, tel, cartype, type, balance);
}

void MainWindow::sqlupdateinfo(QString name, QString tel, QString carid, QString cartype){
    QSqlQuery query;
    QString str = QString("update userinfo set name = '%1' where id = '%2'").arg(name).arg(userid);
    query.exec(str);
    QString str_2 = QString("update userinfo set tel = '%1' where id = '%2'").arg(tel).arg(userid);
    query.exec(str_2);
    QString str_3 = QString("update carinfo set carid = '%1' where id = '%2'").arg(carid).arg(userid);
    query.exec(str_3);
    QString str_4 = QString("update carinfo set cartype = '%1' where id = '%2'").arg(cartype).arg(userid);
    query.exec(str_4);
    QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("修改成功"), QMessageBox::Yes);
    this->sqlinfo();
}

void MainWindow::sqlupdatepass(QString oldpass, QString newpass){
    QSqlQuery query;
    QString inquire = QString("select password from userinfo where id = '%1'").arg(userid);
    query.exec(inquire);
    QString nowpass;
    while(query.next()){
        nowpass = query.value(0).toString();
    }
    if(nowpass != oldpass){
        QMessageBox::warning(nullptr, QStringLiteral("错误"), QStringLiteral("输入的旧密码不正确"), QMessageBox::Yes);
    }
    else{
        QString str = QString("update userinfo set password = '%1' where id = '%2'").arg(newpass).arg(userid);
        query.exec(str);
        QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("修改成功"), QMessageBox::Yes);
    }
}

void MainWindow::sqlupdatebalance(int balance){
    QSqlQuery query;
    QString inquire = QString("select balance from userinfo where id = '%1'").arg(userid);
    query.exec(inquire);
    while(query.next()){
        balance += query.value(0).toInt();
    }
    QString str = QString("update userinfo set balance = '%1' where id = '%2'").arg(balance).arg(userid);
    query.exec(str);
    QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("充值成功"), QMessageBox::Yes);
    this->sqlinfo();
}

void MainWindow::sqlyearmember(){
    QSqlQuery query;
    QString inquire = QString("select balance from userinfo where id = '%1'").arg(userid);
    query.exec(inquire);
    int balance = 0;
    while(query.next()){
        balance = query.value(0).toInt();
    }
    if(balance < 2500){
        QMessageBox::warning(nullptr, QStringLiteral("错误"), QStringLiteral("余额不足，请充值"), QMessageBox::Yes);
    }
    else{
        balance -= 2500;
        QString str = QString("update userinfo set balance = '%1' where id = '%2'").arg(balance).arg(userid);
        QString str_2 = QString("update userinfo set type = '年费会员' where id = '%1'").arg(userid);
        query.exec(str);
        query.exec(str_2);
        QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("会员办理成功"), QMessageBox::Yes);
        this->sqlinfo();
    }
}

void MainWindow::sqlmonthmember(){
    QSqlQuery query;
    QString inquire = QString("select balance from userinfo where id = '%1'").arg(userid);
    query.exec(inquire);
    int balance = 0;
    while(query.next()){
        balance = query.value(0).toInt();
    }
    QString inquire_2 = QString("select type from userinfo where id = '%1'").arg(userid);
    query.exec(inquire_2);
    QString type;
    while(query.next()){
        type = query.value(0).toString();
    }
    if(type == "年费会员"){
        QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("您已是年费会员"), QMessageBox::Yes);
    }
    else{
        if(balance < 260){
            QMessageBox::warning(nullptr, QStringLiteral("错误"), QStringLiteral("余额不足，请充值"), QMessageBox::Yes);
        }
        else{
            balance -= 260;
            QString str = QString("update userinfo set balance = '%1' where id = '%2'").arg(balance).arg(userid);
            QString str_2 = QString("update userinfo set type = '月费会员' where id = '%1'").arg(userid);
            query.exec(str);
            query.exec(str_2);
            QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("会员办理成功"), QMessageBox::Yes);
            this->sqlinfo();
        }
    }

}

void MainWindow::sqlreservation(QString parkingname, int carpos, QDateTime statime, QDateTime endtime){
    int flag = 0;
    QSqlQuery query;
    QString inquire = QString("select finish from book where id = '%1'").arg(userid);
    query.exec(inquire);
    QString fin;
    while(query.next()){
        fin = query.value(0).toString();
        if(fin == "no"){
            flag = 1;
            QMessageBox::warning(nullptr, QStringLiteral("错误"), QStringLiteral("您有一个订单在进行中"), QMessageBox::Yes);
        }
    }
    if(!flag){
        QString inquire_2 = QString("select situation from parkingspace where carpos = '%1' and parkingname = '%2'").arg(carpos).arg(parkingname);
        if(query.exec(inquire_2)){
            QString rec;
            while(query.next()){
                rec = query.value(0).toString();
            }
            if(rec == "空闲"){
                QString inquire_3 = QString("select carpostype from parkingspace where carpos = '%1' and parkingname = '%2'").arg(carpos).arg(parkingname);
                query.exec(inquire_3);
                QString rec_2;
                while(query.next()){
                    rec_2 = query.value(0).toString();
                }
                QString inquire_4 = QString("select cartype from carinfo where id = '%1'").arg(userid);
                query.exec(inquire_4);
                QString rec_3;
                while(query.next()){
                    rec_3 = query.value(0).toString();
                }
                if(rec_2 == rec_3){
                    QString str = QString("update parkingspace set situation = '占用' where carpos = '%1' and parkingname = '%2'").arg(carpos).arg(parkingname);
                    query.exec(str);
                    QString statim = statime.toString("yyyy-MM-dd hh:mm:ss");
                    QString endtim = endtime.toString("yyyy-MM-dd hh:mm:ss");
                    QString str_2 = QString("update parkingspace set statime = '%1' where carpos = '%2' and parkingname = '%3'").arg(statim).arg(carpos).arg(parkingname);
                    query.exec(str_2);
                    QString str_5 = QString("update parkingspace set endtime = '%1' where carpos = '%2' and parkingname = '%3'").arg(endtim).arg(carpos).arg(parkingname);
                    query.exec(str_5);
                    int curorder = 0;
                    QString inquire_5 = QString("select max(ordernum) from book");
                    query.exec(inquire_5);
                    while(query.next()){
                        curorder = query.value(0).toInt();
                    }
                    curorder += 1;
                    QString str_3 = QString("insert into book(id,parkingname,carpos,statime,endtime,finish,ordernum) values('%1', '%2', '%3', '%4', '%5', 'no', '%6')").arg(userid).arg(parkingname).arg(carpos).arg(statim).arg(endtim).arg(curorder);
                    query.exec(str_3);
                    QString str_4 = QString("update parkinglot set emptynum = emptynum - 1 where parkingname = '%1'").arg(parkingname);
                    query.exec(str_4);
                    this->sqlinq();
                    QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("预约成功"), QMessageBox::Yes);
                }
                else{
                    QMessageBox::warning(nullptr, QStringLiteral("错误"), QStringLiteral("该车位的适停车型与您的车型不符合"), QMessageBox::Yes);
                }
            }
            else{
                QMessageBox::warning(nullptr, QStringLiteral("错误"), QStringLiteral("停车场的此车位已被占用"), QMessageBox::Yes);
            }
        }
        else{
            QMessageBox::warning(nullptr, QStringLiteral("错误"), QStringLiteral("输入的停车场或车位号不存在"), QMessageBox::Yes);
        }
    }
}

void MainWindow::updatetimeout(){
    QDateTime curtime = QDateTime::currentDateTime();
    QSqlQuery query;
    QString inquire = QString("select finish from book where id = '%1'").arg(userid);
    query.exec(inquire);
    QString fin;
    while(query.next()){
        fin = query.value(0).toString();
    }
    if(fin == "no"){
        QString inquire_2 = QString("select endtime from book where id = '%1'").arg(userid);
        query.exec(inquire_2);
        QDateTime endtime;
        while(query.next()){
            endtime = query.value(0).toDateTime();
        }
        int elapsed = endtime.msecsTo(curtime);

        QString inquire_4 = QString("select statime from book where id = '%1'").arg(userid);
        query.exec(inquire_4);
        QDateTime statime;
        while(query.next()){
            statime = query.value(0).toDateTime();
        }
        int elapsed_2 = statime.msecsTo(curtime);

        double hours = elapsed * 1.0 / 1000 / 3600;
        double hours_2 = elapsed_2 * 1.0 / 1000 / 3600;
        int duration = ceil(hours);
        int duration_2 = ceil(hours_2);
        int money = 0;
        QString inquire_3 = QString("select type from userinfo where id = '%1'").arg(userid);
        query.exec(inquire_3);
        QString rec;
        while(query.next()){
            rec = query.value(0).toString();
        }
        if(rec == "普通用户"){
            money = duration_2 * 3;
        }
        if(elapsed > 0){
            user.setpayment(duration, money);
        }
        else {
            user.setpayment(0, money);
        }
    }
}

void MainWindow::sqlpayment(int duration, int money){
    QSqlQuery query;
    QString inquire = QString("select balance from userinfo where id = '%1'").arg(userid);
    query.exec(inquire);
    int balance = 0;
    while(query.next()){
        balance = query.value(0).toInt();
    }
    if(balance < money){
        QMessageBox::warning(nullptr, QStringLiteral("错误"), QStringLiteral("余额不足，请先充值"), QMessageBox::Yes);
    }
    else{
        QString str = QString("update book set finish = 'yes' where id = '%1'").arg(userid);
        query.exec(str);

        QString inquire_2 = QString("select parkingname from book where id = '%1'").arg(userid);
        query.exec(inquire_2);
        QString parkingname;
        while(query.next()){
            parkingname = query.value(0).toString();
        }

        QString inquire_3 = QString("select carpos from book where id = '%1'").arg(userid);
        query.exec(inquire_3);
        int carpos = 0;
        while(query.next()){
            carpos = query.value(0).toInt();
        }

        QString inquire_4 = QString("select ordernum from book where id = '%1'").arg(userid);
        query.exec(inquire_4);
        int ordernum = 0;
        while(query.next()){
            ordernum = query.value(0).toInt();
        }

        QString inquire_5 = QString("select statime from book where id = '%1'").arg(userid);
        query.exec(inquire_5);
        QDateTime statime;
        while(query.next()){
            statime = query.value(0).toDateTime();
        }

        QString inquire_6 = QString("select endtime from book where id = '%1'").arg(userid);
        query.exec(inquire_6);
        QDateTime endtime;
        while(query.next()){
            endtime = query.value(0).toDateTime();
        }

        QString str_2 = QString("update parkinglot set emptynum = emptynum + 1 where parkingname = '%1'").arg(parkingname);
        query.exec(str_2);
        QString str_3 = QString("update parkinglot set income = income + '%1' where parkingname = '%2'").arg(money).arg(parkingname);
        query.exec(str_3);
        QString str_4 = QString("update parkingspace set situation = '空闲' where carpos = '%1' and parkingname = '%2'").arg(carpos).arg(parkingname);
        query.exec(str_4);
        QString str_5 = QString("update userinfo set balance = balance - '%1' where id = '%2'").arg(money).arg(userid);
        query.exec(str_5);

        QString statim = statime.toString("yyyy-MM-dd hh:mm:ss");
        QString endtim = endtime.toString("yyyy-MM-dd hh:mm:ss");
        QString str_6 = QString("insert into consumption(id,ordernum,carpos,parkingname,statime,endtime,timeout,fare) values('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8')").arg(userid).arg(ordernum).arg(carpos).arg(parkingname).arg(statim).arg(endtim).arg(duration).arg(money);
        query.exec(str_6);
        this->sqlinq();
        this->sqlinfo();
        QMessageBox::information(nullptr, QStringLiteral("提示"), QStringLiteral("订单完成"), QMessageBox::Yes);
    }
}

void MainWindow::sqlconsumption(){
    QSqlQuery query;
    QString inquire = QString("select * from consumption where id = '%1'").arg(userid);
    query.exec(inquire);
    int i = 0;
    while(query.next()){
        str[i][0] = query.value(0).toString();
        str[i][1] = query.value(3).toString();
        num[i][0] = query.value(1).toInt();
        num[i][1] = query.value(2).toInt();
        num[i][2] = query.value(6).toInt();
        num[i][3] = query.value(7).toInt();
        tim[i][0] = query.value(4).toDateTime();
        tim[i][1] = query.value(5).toDateTime();
        i++;
    }
    len_2 = i;
    user.recordprint(str, num, tim, len_2);
}

void MainWindow::sqlparkinglot(){
    QSqlQuery query;
    QString inquire = QString("select * from parkinglot where parkingid = '%1'").arg(parkerid);
    query.exec(inquire);
    int posnum = 0, emptynum = 0, income = 0;
    while(query.next()){
        posnum = query.value(1).toInt();
        emptynum = query.value(2).toInt();
        income = query.value(3).toInt();
    }
    parker.setline(posnum, emptynum, income);
}

void MainWindow::sqlparkingspace(){
    QSqlQuery query;
    QString inquire = QString("select parkingname from parkinglot where parkingid = '%1'").arg(parkerid);
    query.exec(inquire);
    QString parkingname;
    while(query.next()){
        parkingname = query.value(0).toString();
    }
    QString inquire_2 = QString("select * from book where parkingname = '%1' and finish = 'no'").arg(parkingname);
    query.exec(inquire_2);
    int i = 0;
    while(query.next()){
        parkingstr[i] = query.value(0).toString();
        parkingnum[i] = query.value(2).toInt();
        parkingtim[i][0] = query.value(3).toDateTime();
        parkingtim[i][1] = query.value(4).toDateTime();
        i++;
    }
    len_3 = i;
    parker.print(parkingstr, parkingnum, parkingtim, len_3);
}

void MainWindow::quit(){
    user.close();
    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
