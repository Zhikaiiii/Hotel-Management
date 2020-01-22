#include "seehotel.h"
#include "ui_seehotel.h"
#include "logindiag.h"
#include "mainwindow_customer.h"
#include "data.h"
#include <QString>
#include <QDebug>
#include<QMessageBox>

seeHotel::seeHotel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::seeHotel)
{
    ui->setupUi(this);
    //界面美化
    ui->totalprice->setText(QString::number(selecthotel->returnHotelPrice(0)));
    ui->totalprice->setEnabled(false);
    ui->Single->setEnabled(false);
    ui->Double->setEnabled(false);
    ui->Family->setEnabled(false);
    ui->Luxury->setEnabled(false);
    QPixmap pixmap = QPixmap(":/images/2.png").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
}

seeHotel::~seeHotel()
{
    delete ui;
}

void seeHotel::show()
{

    QString singleroom=QString::number(selecthotel->returnLeftRoomnumber(0))+"/"+QString::number(selecthotel->returnRoomnumber(0));
    QString doubleroom=QString::number(selecthotel->returnLeftRoomnumber(1))+"/"+QString::number(selecthotel->returnRoomnumber(1));
    QString familyroom=QString::number(selecthotel->returnLeftRoomnumber(2))+"/"+QString::number(selecthotel->returnRoomnumber(2));
    QString luxuryroom=QString::number(selecthotel->returnLeftRoomnumber(3))+"/"+QString::number(selecthotel->returnRoomnumber(3));
    ui->Single->setText(singleroom);
    ui->Double->setText(doubleroom);
    ui->Family->setText(familyroom);
    ui->Luxury->setText(luxuryroom);
    ui->totalprice->setText(QString::number((ui->roomnumber->currentIndex()+1)*(selecthotel->returnHotelPrice(ui->roomType->currentIndex()))));
    ui->name->setText(selecthotel->returnInfo(1));
    ui->location->setText(selecthotel->returnInfo(2));
    ui->feature->setText(selecthotel->returnInfo(3));
    ui->star->setText(selecthotel->returnInfo(4));
    QString score=QString::number(selecthotel->calScore());
    ui->score->setText(score);
    //显示各个房间余量信息以及酒店信息
    QMainWindow::show();
}

void seeHotel::on_pushButton_clicked()//下单
{
    int roomnumber=ui->roomnumber->currentIndex()+1;
    int type=ui->roomType->currentIndex();
    if(roomnumber>selecthotel->returnLeftRoomnumber(type))
    {
        QMessageBox::QMessageBox::warning(this, tr("警告！"),tr("房间余额不足！"), QMessageBox::Yes);
    }
    else
    {
        Room_Type Type=Room_Type(type);
        loginuser->addOrder(Type,roomnumber);
        qDebug()<<"dydydy";
        QMessageBox::QMessageBox::information(this, tr("提示！"),tr("下单成功,您可在订单页面查看详细信息！"), QMessageBox::Yes);
    }
}

void seeHotel::on_pushButton_3_clicked()
{
    this->close();
}

//实时更新订单总价
void seeHotel::on_roomType_currentIndexChanged(int index)
{
    int type=ui->roomType->currentIndex();
    int number=ui->roomnumber->currentIndex()+1;
    int totalprice=(selecthotel->returnHotelPrice(type))*number;
    ui->totalprice->setText(QString::number(totalprice));
}

void seeHotel::on_roomnumber_currentIndexChanged(int index)
{
    int type=ui->roomType->currentIndex();
    int number=ui->roomnumber->currentIndex()+1;
    int totalprice=(selecthotel->returnHotelPrice(type))*number;
    ui->totalprice->setText(QString::number(totalprice));
}
