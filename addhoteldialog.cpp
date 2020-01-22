#include "addhoteldialog.h"
#include "ui_addhoteldialog.h"
#include <QString>
#include <QMessageBox>
#include "mainwindow.h"
#include "data.h"


addHotelDialog::addHotelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addHotelDialog)
{
    ui->setupUi(this);
    //界面美化
    QPixmap pixmap = QPixmap(":/images/2.png").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
}

addHotelDialog::~addHotelDialog()
{
    delete ui;
}

void addHotelDialog::on_pushButton_regi_clicked()//注册新酒店
{
    QString Name=ui->lineEdit_Name->text();
    QString Location=ui->lineEdit_Location->text();
    QString Feature=ui->lineEdit_Feature->text();
    QString Id=ui->lineEdit_Id->text();
  //  QString Owner=loginuser->returnId();
    //State H_State=Waiting;
    int Star=(ui->comboBox_star->currentIndex()+2);
    if(Name.length()==0||Location.length()==0||Id.length()==0||Feature.length()==0)//规范性判断
    {
        QMessageBox::QMessageBox::warning(this, tr("警告！"),tr("请完善酒店信息！"), QMessageBox::Yes);
    }
    else
    {
        //Hotel *h=new Hotel(Name,Location,Feature,Star,Id,H_State,Owner);
        //insert_Data(h);
        loginuser->addHotel(Name,Location,Feature,Star,Id);
        QMessageBox::QMessageBox::information(this, tr("提示！"),tr("注册成功,请等待管理员审核！"), QMessageBox::Yes);
        this->close();
        MainWindow *mainwindow=new MainWindow(this);
        mainwindow->show();
    }
}

void addHotelDialog::on_pushButton_exit_clicked()//返回酒店老板主界面
{
    this->close();

}


