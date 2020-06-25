#include "record.h"
#include "ui_record.h"

record::record(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::record)
{
    ui->setupUi(this);

    QPixmap pixmap = QPixmap(":/timg.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

    pLayout = new QGridLayout();
    pLayout->setSpacing(20);
    pLayout->setAlignment(Qt::AlignTop);
}
\
void record::print(QString (*str)[2], int (*num)[4], QDateTime (*time)[2], int len){
    for(int i = 0; i < len; ++i)
    {
        if(i == 0)
        {
            QLayoutItem *child;
            while ((child = pLayout->takeAt(0)) != nullptr)
            {
                if(child->widget())
                {
                    child->widget()->setParent(nullptr);
                }
                delete child;

            }
            ui->scrollArea->widget()->setLayout(pLayout);
        }
        QLineEdit *lineEdit = new QLineEdit();
        QLineEdit *lineEdit_2 = new QLineEdit();
        QLineEdit *lineEdit_3 = new QLineEdit();
        QLineEdit *lineEdit_4 = new QLineEdit();
        QLineEdit *lineEdit_5 = new QLineEdit();
        QLineEdit *lineEdit_6 = new QLineEdit();
        QLineEdit *lineEdit_7 = new QLineEdit();
        QLineEdit *lineEdit_8 = new QLineEdit();
        lineEdit->setReadOnly(true);
        lineEdit_2->setReadOnly(true);
        lineEdit_3->setReadOnly(true);
        lineEdit_4->setReadOnly(true);
        lineEdit_5->setReadOnly(true);
        lineEdit_6->setReadOnly(true);
        lineEdit_7->setReadOnly(true);
        lineEdit_8->setReadOnly(true);

        lineEdit->setAlignment(Qt::AlignHCenter);
        lineEdit_2->setAlignment(Qt::AlignHCenter);
        lineEdit_3->setAlignment(Qt::AlignHCenter);
        lineEdit_4->setAlignment(Qt::AlignHCenter);
        lineEdit_5->setAlignment(Qt::AlignHCenter);
        lineEdit_6->setAlignment(Qt::AlignHCenter);
        lineEdit_7->setAlignment(Qt::AlignHCenter);
        lineEdit_8->setAlignment(Qt::AlignHCenter);

        lineEdit_2->setText(QString::number(num[i][0]));
        lineEdit_3->setText(QString::number(num[i][1]));
        lineEdit_7->setText(QString::number(num[i][2]));
        lineEdit_8->setText(QString::number(num[i][3]));
        lineEdit->setText(str[i][0]);
        lineEdit_4->setText(str[i][1]);
        QString statim = time[i][0].toString("yyyy-MM-dd hh:mm:ss");
        QString endtim = time[i][1].toString("yyyy-MM-dd hh:mm:ss");
        lineEdit_5->setText(statim);
        lineEdit_6->setText(endtim);

        pLayout->addWidget(lineEdit, i, 0, 1, 1);
        pLayout->addWidget(lineEdit_2, i, 1, 1, 1);
        pLayout->addWidget(lineEdit_3, i, 2, 1, 1);
        pLayout->addWidget(lineEdit_4, i, 3, 1, 1);
        pLayout->addWidget(lineEdit_5, i, 4, 1, 1);
        pLayout->addWidget(lineEdit_6, i, 5, 1, 1);
        pLayout->addWidget(lineEdit_7, i, 6, 1, 1);
        pLayout->addWidget(lineEdit_8, i, 7, 1, 1);
    }
    ui->scrollArea->widget()->setLayout(pLayout);
}

record::~record()
{
    delete ui;
}
