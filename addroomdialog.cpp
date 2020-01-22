#include "addroomdialog.h"
#include "ui_addroomdialog.h"
#include "allofroom.h"
#include "mainwindow.h"
#include "data.h"
#include <QString>
#include <QMessageBox>

addRoomDialog::addRoomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addRoomDialog)
{
    ui->setupUi(this);
    //价格可编辑与否判断
    if(selecthotel->returnHotelPrice(0)!=0)
    {
        ui->lineEdit_price->setEnabled(false);
        ui->lineEdit_price->setText(QString::number(selecthotel->returnHotelPrice(0)));
    }
     //界面美化
    QPixmap pixmap = QPixmap(":/images/2.png").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
}

addRoomDialog::~addRoomDialog()
{
    delete ui;
}

void addRoomDialog::on_pushButton_2_clicked()//返回
{
    this->close();
}

void addRoomDialog::on_pushButton_clicked()
{
    QString TypeName=ui->comboBox_type->currentText();
    Room_Type Type;
    if(TypeName==" 单人房")
    {
        Type=Single;
    }
    else if(TypeName==" 双人房")
    {
        Type=Double;
    }
    else if(TypeName==" 家庭房")
    {
        Type=Family;
    }
    else if(TypeName==" 豪华套房")
    {
            Type=Luxurious;
    }
    int size1=ui->lineEdit_roomnumber->text().length();
    bool judge=true;
    //规范性判断
    if(size1==0)
    {
        judge=false;
        QMessageBox::QMessageBox::warning(this, tr("提示！"),tr("房间号输入不规范！"), QMessageBox::Yes);
    }
    else
    {
        for(int i=0;i<size1;i++)
        {
            if(ui->lineEdit_roomnumber->text()[i]<'0'||
                    ui->lineEdit_roomnumber->text()[i]>'9')
            {
                judge=false;
                QMessageBox::QMessageBox::warning(this, tr("提示！"),tr("房间号输入不规范！"), QMessageBox::Yes);
                break;
            }
        }
    }
    int size2=ui->lineEdit_price->text().length();
    if(size2==0)
    {
        judge=false;
        QMessageBox::QMessageBox::warning(this, tr("提示！"),tr("请输入正确的定价！"), QMessageBox::Yes);
    }
    else
    {
        for(int i=0;i<size2;i++)
        {
            if(ui->lineEdit_price->text()[i]<'0'||
                    ui->lineEdit_price->text()[i]>'9')
            {
                judge=false;
                QMessageBox::QMessageBox::warning(this, tr("提示！"),tr("请输入正确的定价！"), QMessageBox::Yes);
                break;
            }
        }
    }
    //添加房间
    if(judge)
    {
        int Price=ui->lineEdit_price->text().toInt();
        int Roomnumber=ui->lineEdit_roomnumber->text().toInt();
        int state=0;
        new_room[new_room_number]=selecthotel->addRoom(Price,Type,Roomnumber,state);
        //调用hotel类的addRoom来添加房间并将其赋值给new_room指针数组
        new_room_number++;
        QMessageBox::QMessageBox::information(this, tr("提示！"),tr("房间添加成功！"), QMessageBox::Yes);
        this->close();
    }
}

void addRoomDialog::on_comboBox_type_currentIndexChanged(int index)//房间类型combobox变化时价格可编辑性判断
{
    int type=ui->comboBox_type->currentIndex();
    if(selecthotel->returnHotelPrice(type)!=0)
    {
        ui->lineEdit_price->setEnabled(false);
        ui->lineEdit_price->setText(QString::number(selecthotel->returnHotelPrice(type)));
    }
    else
    {
        ui->lineEdit_price->setEnabled(true);
        ui->lineEdit_price->clear();
    }
}
