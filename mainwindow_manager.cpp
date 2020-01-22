#include "mainwindow_manager.h"
#include "ui_mainwindow_manager.h"
#include "logindiag.h"
#include "data.h"
#include "scorecustomerdialog.h"
#include <QString>
#include <QMessageBox>
MainWindow_manager::MainWindow_manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_manager)
{
    ui->setupUi(this);
    //界面美化
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    QPixmap pixmap = QPixmap(":/images/2.png").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
    ui->hotel->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgba(0,0,0,0)};");
    ui->hotel->verticalHeader()->hide();
    ui->order->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgba(0,0,0,0)};");
    ui->order->verticalHeader()->hide();

}

MainWindow_manager::~MainWindow_manager()
{
    delete ui;
}

void MainWindow_manager::on_pushButton_clicked()//退出登录
{
    LoginDiag *log =new LoginDiag(this);
    this->hide();
    log->show();
}

void MainWindow_manager::showHotelInfo() const//显示酒店信息
{
    QString bossId=now_manager.value(loginuser->returnId());
    int Size=all_hotel.size();
    int nRow=0;
    int j=0;
    for(int i=0;i<Size;i++)
    {
        if(all_hotel.value(hotel[i])->returnOwner()==bossId
           && all_hotel.value(hotel[i])->returnState()==Pass)//判断酒店是否符合条件
        {
            nRow++;
        }
    }
    ui->hotel->setRowCount(nRow);
    for(int i=0;i<Size;i++)
    {
        if(all_hotel.value(hotel[i])->returnOwner()==bossId
           && all_hotel.value(hotel[i])->returnState()==Pass)
        {
            for(int k=0;k<6;k++)
            {
                QTableWidgetItem *item = new QTableWidgetItem;
                item->setText(all_hotel.value(hotel[i])->returnInfo(k));
                item->setTextAlignment(Qt::AlignHCenter);
                ui->hotel->setItem(j, k, item);
            }
            j++;
        }
     }
}

void MainWindow_manager::SetItem(int i, int j)//设定order的tablewidget内容,i为订单号，j为第j行
{
    QTableWidgetItem *item0 = new QTableWidgetItem;
    QTableWidgetItem *item1 = new QTableWidgetItem;
    QTableWidgetItem *item2 = new QTableWidgetItem;
    QTableWidgetItem *item3 = new QTableWidgetItem;
    item0->setText(all_order.value(i)->returnInfo(0));
    item1->setText(all_order.value(i)->returnInfo(2));
    item2->setText(all_order.value(i)->returnInfo(3));
    item3->setText(all_order.value(i)->returnInfo(4));
    item0->setTextAlignment(Qt::AlignHCenter);
    item1->setTextAlignment(Qt::AlignHCenter);
    item2->setTextAlignment(Qt::AlignHCenter);
    item3->setTextAlignment(Qt::AlignHCenter);
    ui->order->setItem(j, 0, item0);
    ui->order->setItem(j, 1, item1);
    ui->order->setItem(j, 2, item2);
    ui->order->setItem(j, 3, item3);
}

void MainWindow_manager::showOrderInfo()//显示订单信息
{
    QList<QTableWidgetSelectionRange>ranges=ui->hotel->selectedRanges();
    int Row=ranges.at(0).topRow();
    QString Id=ui->hotel->item(Row,0)->text();
    int nRow=0;
    selecthotel=all_hotel.value(Id);
    for(int i=0;i<all_order_number;i++)
    {
        if(all_order.value(i)->returnHotel()==Id)
        {
            nRow++;
        }
    }
    ui->order->setRowCount(nRow);
    int j=0;
    for(int i=0;i<all_order_number;i++)
    {
        if(all_order.value(i)->returnHotel()==Id)
        {
            SetItem(i,j);
            j++;
        }
    }
}

void MainWindow_manager::show()//重载
{
    QMainWindow::show();
    showHotelInfo();
}

void MainWindow_manager::showDetailed()//显示订单详情
{
    QList<QTableWidgetSelectionRange>ranges=ui->order->selectedRanges();
    int Row=ranges.at(0).topRow();
    int Num=ui->order->item(Row,0)->text().toInt();
    selectorder=all_order.value(Num);
    ui->ordernum->setText(selectorder->returnInfo(0));
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

void MainWindow_manager::on_pushButton_2_clicked()
{
    show();
    showOrderInfo();
}

void MainWindow_manager::on_pushButton_3_clicked()
{
    show();
    showOrderInfo();
    showDetailed();
}

void MainWindow_manager::on_pushButton_4_clicked()//改变顾客入住状态
{
    int state=ui->changeorderstate->currentIndex();
    if(state==0)
    {
        selectorder->changeState(Order_State(state));
    }
    else
    {
        selectorder->changeState(Order_State(state+2));
    }
    show();
    showOrderInfo();
    showDetailed();
}

void MainWindow_manager::on_pushButton_5_clicked()//受理顾客退款
{
    if(selectorder->returnState()==1)
    {
        selectorder->changeState(Order_State(2));
    }
    show();
    showOrderInfo();
    showDetailed();
}

void MainWindow_manager::on_pushButton_6_clicked()//投诉顾客界面
{
    if(selectorder->returnState()==4&&selectorder->returnCscore()==0)
    {
        ScoreCustomerDialog *log=new ScoreCustomerDialog(this);
        log->show();
    }
    else if(selectorder->returnState()==4&&selectorder->returnCscore()!=0)
    {
         QMessageBox::QMessageBox::warning(this, tr("警告！"),tr("您已经投诉过该顾客！"), QMessageBox::Yes);
    }
    else
    {
         QMessageBox::QMessageBox::warning(this, tr("警告！"),tr("您当前不能投诉顾客！"), QMessageBox::Yes);
    }
}
//程序容错性设置
void MainWindow_manager::on_hotel_cellClicked(int row, int column)
{
    ui->pushButton_2->setEnabled(true);
}

void MainWindow_manager::on_order_cellClicked(int row, int column)
{
    ui->pushButton_3->setEnabled(true);
}

void MainWindow_manager::on_hotel_itemSelectionChanged()
{
    if(ui->hotel->selectedItems().size()==0)
    {
        ui->pushButton_2->setEnabled(false);
    }
}

void MainWindow_manager::on_order_itemSelectionChanged()
{
    if(ui->order->selectedItems().size()==0)
    {
        ui->pushButton_3->setEnabled(false);
    }
}
//保存数据
void MainWindow_manager::closeEvent(QCloseEvent *event)
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
