#include "mainwindow_customer_order.h"
#include "ui_mainwindow_customer_order.h"
#include "logindiag.h"
#include "data.h"
#include "customerdialog.h"
#include "scorehoteldialog.h"
#include <QMessageBox>


MainWindow_customer_order::MainWindow_customer_order(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_customer_order)
{
    ui->setupUi(this);
    //界面美化
    ui->pushButton_3->setEnabled(false);
    QPixmap pixmap = QPixmap(":/images/2.png").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
    ui->OrderInfo->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgba(0,0,0,0)};");
    ui->OrderInfo->verticalHeader()->hide();
}

MainWindow_customer_order::~MainWindow_customer_order()
{
    delete ui;
}

void MainWindow_customer_order::SetItem(int i, int j)//设定tablewidget每项内容，i为第i个订单，j为第j行
{
    QTableWidgetItem *item0 = new QTableWidgetItem;
    QTableWidgetItem *item1 = new QTableWidgetItem;
    QTableWidgetItem *item2 = new QTableWidgetItem;
    QTableWidgetItem *item3 = new QTableWidgetItem;
    item0->setText(all_order.value(i)->returnInfo(0));
    item1->setText(all_order.value(i)->returnInfo(1));
    item2->setText(all_order.value(i)->returnInfo(3));
    item3->setText(all_order.value(i)->returnInfo(4));
    item0->setTextAlignment(Qt::AlignHCenter);
    item1->setTextAlignment(Qt::AlignHCenter);
    item2->setTextAlignment(Qt::AlignHCenter);
    item3->setTextAlignment(Qt::AlignHCenter);
    ui->OrderInfo->setItem(j, 0, item0);
    ui->OrderInfo->setItem(j, 1, item1);
    ui->OrderInfo->setItem(j, 2, item2);
    ui->OrderInfo->setItem(j, 3, item3);
}

void MainWindow_customer_order::showOrderInfo()
{
    int nRow=0;//设定tablewidget的行数
    for(int i=0;i<all_order_number;i++)
    {
        if(all_order.value(i)->returnCustomer()==loginuser->returnId())
        {
            nRow++;
        }
    }
    ui->OrderInfo->setRowCount(nRow);
    int j=0;
    for(int i=0;i<all_order_number;i++)
    {
        if(all_order.value(i)->returnCustomer()==loginuser->returnId())
        {
            SetItem(i,j);
            j++;
        }
    }
}

void MainWindow_customer_order::show()//重载show函数
{
    QMainWindow::show();
    showOrderInfo();
}

void MainWindow_customer_order::on_pushButton_clicked()//退出登录
{
    LoginDiag *log=new LoginDiag(this);
    this->hide();
    log->show();
}

void MainWindow_customer_order::on_pushButton_2_clicked()//返回顾客界面
{
    customerDialog *log =new customerDialog(this);
    this->hide();
    log->show();
}

void MainWindow_customer_order::showDetailed()//显示订单信息
{
    ui->name->setText(selecthotel->returnInfo(1));
    ui->location->setText(selecthotel->returnInfo(2));
    ui->feature->setText(selecthotel->returnInfo(3));
    ui->star->setText(selecthotel->returnInfo(4));
    ui->roomtype->setText(selectorder->returnInfo(5));
    ui->roomnumber->setText(selectorder->returnInfo(6));
    QString roomsnumber=NULL;
    for(int k=0;k<selectorder->returnNumber();k++)
    {
         roomsnumber=roomsnumber+QString::number(selectorder->returnRoomsNumber(k))+" ";
    }
    ui->roomnumber_->setText(roomsnumber);
    ui->orderstate->setText(selectorder->returnInfo(7));
}
void MainWindow_customer_order::on_pushButton_3_clicked()//选定订单查看
{
    QList<QTableWidgetSelectionRange>ranges=ui->OrderInfo->selectedRanges();
    int Row=ranges.at(0).topRow();
    QString Id=ui->OrderInfo->item(Row,1)->text();
    int orderId=ui->OrderInfo->item(Row,0)->text().toInt();
    selecthotel=all_hotel.value(Id);
    selectorder=all_order.value(orderId);
    show();
    showDetailed();
}

void MainWindow_customer_order::on_pushButton_4_clicked()//若订单以退房且为评价，则评价
{
    if(selectorder->returnState()==4&&selectorder->returnHscore()==0)
    {
        ScoreHotelDialog *log=new ScoreHotelDialog(this);
        log->show();
    }
    else if(selectorder->returnState()==4&&selectorder->returnHscore()==0)
    {
        QMessageBox::QMessageBox::warning(this, tr("警告！"),tr("您已经评价过了！"), QMessageBox::Yes);
    }
    else
    {
        QMessageBox::QMessageBox::warning(this, tr("警告！"),tr("您当前不能评价！"), QMessageBox::Yes);
    }
}

void MainWindow_customer_order::on_pushButton_5_clicked()//退款及其判断
{
    if(selectorder->returnState()==0)
    {
        selectorder->changeState(Order_State(1));
        QMessageBox::QMessageBox::warning(this, tr("提示！"),tr("退款成功！"), QMessageBox::Yes);
    }
    else
    {
        QMessageBox::QMessageBox::warning(this, tr("警告！"),tr("您当前不能退款！"), QMessageBox::Yes);
    }
    show();
    showDetailed();
}
//程序容错性设置
void MainWindow_customer_order::on_OrderInfo_cellClicked(int row, int column)
{
    ui->pushButton_3->setEnabled(true);
}



void MainWindow_customer_order::on_OrderInfo_itemSelectionChanged()
{
    if(ui->OrderInfo->selectedItems().size()==0)
    {
        ui->pushButton_3->setEnabled(false);
    }
}
//保存数据
void MainWindow_customer_order::closeEvent(QCloseEvent *event)
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
