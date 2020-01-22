#include "customerdialog.h"
#include "ui_customerdialog.h"
#include "datedialog.h"
#include "data.h"
#include "logindiag.h"
#include "mainwindow_customer_order.h"
#include <QDebug>

customerDialog::customerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::customerDialog)
{
    ui->setupUi(this);
    //判断用户是否可预订并进行相应美化及按钮设置
    if(loginuser->returnState()!=0)
    {
        QPixmap pixmap = QPixmap(":/images/6.png").scaled(this->size());
        QPalette  palette (this->palette());
        palette .setBrush(QPalette::Background, QBrush(pixmap));
        this-> setPalette( palette );
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->label_2->show();
        ui->label->close();
    }
    else
    {
        QPixmap pixmap = QPixmap(":/images/3.png").scaled(this->size());
        QPalette  palette (this->palette());
        palette .setBrush(QPalette::Background, QBrush(pixmap));
        this-> setPalette( palette );
        ui->label->show();
        ui->label_2->close();

    }
}

customerDialog::~customerDialog()
{
    delete ui;
}

void customerDialog::on_pushButton_clicked()//进入预定酒店页面
{
    DateDialog *log=new DateDialog(this);
    this->close();
    log->show();
}

void customerDialog::on_pushButton_2_clicked()//进入管理订单页面
{
    MainWindow_customer_order *Mainwindow=new MainWindow_customer_order(this);
    this->close();
    Mainwindow->show();
}

void customerDialog::on_pushButton_3_clicked()//退出登录
{
    LoginDiag *log=new LoginDiag(this);
    this->close();
    log->show();
}
