#include "mainwindow_customer.h"
#include "ui_mainwindow_customer.h"
#include "logindiag.h"
#include "data.h"
#include "datedialog.h"
#include "customerdialog.h"
#include "seehotel.h"
#include <QMessageBox>
MainWindow_customer::MainWindow_customer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_customer)
{
    ui->setupUi(this);
    //界面美化
    ui->pushButton_2->setEnabled(false);
    QPixmap pixmap = QPixmap(":/images/2.png").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
    ui->hotelLookup->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgba(0,0,0,0)};");
    ui->hotelLookup->verticalHeader()->hide();
}

MainWindow_customer::~MainWindow_customer()
{
    delete ui;
}

void MainWindow_customer::on_pushButton_clicked()//登录界面
{
    LoginDiag *log =new LoginDiag(this);
    this->hide();
    log->show();

}

void MainWindow_customer::setItem(int i,int j)//i代表第i个酒店，j代表tablewidget的第j行
{
    int select_type=ui->RoomType->currentIndex();
    QTableWidgetItem *item0 = new QTableWidgetItem;
    QString score=QString::number(all_hotel.value(hotel[i])->calScore(),'f',1);
    item0->setText(score);
    item0->setTextAlignment(Qt::AlignHCenter);
    ui->hotelLookup->setItem(j, 0, item0);
    QTableWidgetItem *item1 = new QTableWidgetItem;
    QTableWidgetItem *item2 = new QTableWidgetItem;
    QTableWidgetItem *item3 = new QTableWidgetItem;
    switch(select_type)
    {
        case 0:
        {
            item1->setText(QString::number(all_hotel.value(hotel[i])->returnHotelPrice(0)));
            item2->setText(QString::number(all_hotel.value(hotel[i])->returnTotalRoomNumber()));
            item3->setText(QString::number(all_hotel.value(hotel[i])->returnTotalLeftRoomNumber()));
            break;
        }
        case 1:
        {
            item1->setText(QString::number(all_hotel.value(hotel[i])->returnHotelPrice(0)));
            item2->setText(QString::number(all_hotel.value(hotel[i])->returnRoomnumber(0)));
            item3->setText(QString::number(all_hotel.value(hotel[i])->returnLeftRoomnumber(0)));
            break;
        }
        case 2:
        {
            item1->setText(QString::number(all_hotel.value(hotel[i])->returnHotelPrice(1)));
            item2->setText(QString::number(all_hotel.value(hotel[i])->returnRoomnumber(1)));
            item3->setText(QString::number(all_hotel.value(hotel[i])->returnLeftRoomnumber(1)));
            break;
        }
        case 3:
        {
            item1->setText(QString::number(all_hotel.value(hotel[i])->returnHotelPrice(2)));
            item2->setText(QString::number(all_hotel.value(hotel[i])->returnRoomnumber(2)));
            item3->setText(QString::number(all_hotel.value(hotel[i])->returnLeftRoomnumber(2)));
            break;
        }
        case 4:
        {
            item1->setText(QString::number(all_hotel.value(hotel[i])->returnHotelPrice(3)));
            item2->setText(QString::number(all_hotel.value(hotel[i])->returnRoomnumber(3)));
            item3->setText(QString::number(all_hotel.value(hotel[i])->returnLeftRoomnumber(3)));
            break;
        }
        default:
        {
            break;
        }
    }
    item1->setTextAlignment(Qt::AlignHCenter);
    item2->setTextAlignment(Qt::AlignHCenter);
    item3->setTextAlignment(Qt::AlignHCenter);
    ui->hotelLookup->setItem(j, 1, item1);
    ui->hotelLookup->setItem(j, 2, item2);
    ui->hotelLookup->setItem(j, 3, item3);
    for(int k=0;k<5;k++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(all_hotel.value(hotel[i])->returnInfo(k));
        item->setTextAlignment(Qt::AlignHCenter);
        ui->hotelLookup->setItem(j, k+4, item);
    }
}
void MainWindow_customer::showHotelInfo()
{
    int Size=all_hotel.size();
    int nRow=0;
    for(int i=0;i<Size;i++)//判断tablawidget的行数
    {
        if(all_hotel.value(hotel[i])->returnState()==Pass)
        {
            nRow++;
            all_hotel.value(hotel[i])->changeLeftnumber(day_in,day_out);//改变酒店的房间余量
        }
    }
    ui->hotelLookup->setRowCount(nRow);
    int j=0;
    for(int i=0;i<Size;i++)
    {
        if(all_hotel.value(hotel[i])->returnState()==Pass)
        {
            setItem(i,j);
            j++;
        }
    }
}

void MainWindow_customer::show()
{
    QMainWindow::show();
    showHotelInfo();
}

void MainWindow_customer::on_RoomType_currentIndexChanged(int index)//根据所需房型变化重新显示
{
    show();
}

void MainWindow_customer::on_pushButton_6_clicked()
{
    SortLeft(ui->RoomType->currentIndex());//按余量排序
    show();
}

void MainWindow_customer::on_pushButton_4_clicked()
{
    SortPrice(ui->RoomType->currentIndex());//按价格排序
    show();
}

void MainWindow_customer::on_pushButton_8_clicked()//按地点查询
{
    QString Location=ui->locationLookup->text();
    int Size=all_hotel.size();
    int nRow=0;
    for(int i=0;i<Size;i++)
    {
        if(all_hotel.value(hotel[i])->returnLocation().contains(Location)
                &&all_hotel.value(hotel[i])->returnState()==Pass)
        {
            nRow++;
        }
    }
    ui->hotelLookup->setRowCount(nRow);
    int j=0;
    for(int i=0;i<Size;i++)
    {
        if(all_hotel.value(hotel[i])->returnLocation().contains(Location)
                &&all_hotel.value(hotel[i])->returnState()==Pass)
        {
            setItem(i,j);
            j++;
        }
    }
    QMainWindow::show();
}

void MainWindow_customer::on_pushButton_3_clicked()//重选日期
{
    customerDialog *log=new customerDialog(this);
    this->hide();
    log->show();
}

void MainWindow_customer::on_pushButton_2_clicked()//进入下单界面
{
    QList<QTableWidgetSelectionRange>ranges=ui->hotelLookup->selectedRanges();
    int Row=ranges.at(0).topRow();
    QString Id=ui->hotelLookup->item(Row,4)->text();
    selecthotel=all_hotel.value(Id);
    seeHotel *Mainwindow=new seeHotel(this);
    Mainwindow->show();
}

void MainWindow_customer::on_hotelLookup_itemClicked(QTableWidgetItem *item)//程序容错性设置
{
    ui->pushButton_2->setEnabled(true);
}

void MainWindow_customer::on_hotelLookup_itemSelectionChanged()
{
    if(ui->hotelLookup->selectedItems().size()==0)
    {
        ui->pushButton_2->setEnabled(false);
    }
}

void MainWindow_customer::on_pushButton_5_clicked()//按评分排序
{
    SortScore();
    show();
}

void MainWindow_customer::closeEvent(QCloseEvent *event)//数据保存
{
    int temp =QMessageBox::question(this,tr("关闭"),tr("是否要关闭程序？"),QMessageBox::Yes,QMessageBox::No);
    if(temp == QMessageBox::Yes)
    {
        savedata();
        savadataH();
        savedataO();
        this->close();
    }
    else
    {
        event->ignore();
    }
}

