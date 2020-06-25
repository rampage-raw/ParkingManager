#include "parkingwindow.h"
#include "ui_parkingwindow.h"

parkingwindow::parkingwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::parkingwindow)
{
    ui->setupUi(this);

    QPixmap pixmap = QPixmap(":/ground_4.jpg").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

    pLayout = new QGridLayout();
    pLayout->setSpacing(20);
    pLayout->setAlignment(Qt::AlignTop);
}

void parkingwindow::print(QString *parkingstr, int *parkingnum, QDateTime (*parkingtim)[2], int len){
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
        lineEdit->setReadOnly(true);
        lineEdit_2->setReadOnly(true);
        lineEdit_3->setReadOnly(true);
        lineEdit_4->setReadOnly(true);

        lineEdit->setAlignment(Qt::AlignHCenter);
        lineEdit_2->setAlignment(Qt::AlignHCenter);
        lineEdit_3->setAlignment(Qt::AlignHCenter);
        lineEdit_4->setAlignment(Qt::AlignHCenter);

        lineEdit->setText(QString::number(parkingnum[i]));
        lineEdit_2->setText(parkingstr[i]);
        QString statim = parkingtim[i][0].toString("yyyy-MM-dd hh:mm:ss");
        QString endtim = parkingtim[i][1].toString("yyyy-MM-dd hh:mm:ss");
        lineEdit_3->setText(statim);
        lineEdit_4->setText(endtim);

        pLayout->addWidget(lineEdit, i, 0, 1, 1);
        pLayout->addWidget(lineEdit_2, i, 1, 1, 1);
        pLayout->addWidget(lineEdit_3, i, 2, 1, 1);
        pLayout->addWidget(lineEdit_4, i, 3, 1, 1);
    }
    ui->scrollArea->widget()->setLayout(pLayout);
}

void parkingwindow::setline(int posnum, int emptynum, int income){
    ui->lineEdit->setText(QString::number(posnum));
    ui->lineEdit_2->setText(QString::number(emptynum));
    ui->lineEdit_3->setText(QString::number(income));
}

parkingwindow::~parkingwindow()
{
    delete ui;
}
