#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindiag.h"
#include "addhoteldialog.h"
#include "allofroom.h"
#include <QMessageBox>
#include <QString>
#include "data.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //界面美化
    ui->pushButton_3->setEnabled(false);
    QPixmap pixmap = QPixmap(":/images/2.png").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
    ui->HotelPass->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgba(0,0,0,0)};");
    ui->HotelPass->verticalHeader()->hide();
    ui->HotelUnPass->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgba(0,0,0,0)};");
    ui->HotelUnPass->verticalHeader()->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_5_clicked()//返回登录界面
{
    LoginDiag *log =new LoginDiag(this);
    this->hide();
    log->show();
}

void MainWindow::on_pushButton_clicked()//跳转至酒店注册界面
{
    addHotelDialog *log =new addHotelDialog(this);
    log->show();
}


void MainWindow::showHotelInfo() const //显示酒店信息
{
    QString Owner=loginuser->returnId();
    int j1=0;
    int j2=0;
    int nRow1=0;
    int nRow2=0;
    int Size=all_hotel.size();
    for(int i=0;i<Size;i++)
    {
        if(all_hotel.value(hotel[i])->returnOwner()==Owner)//判断酒店拥有者及酒店状态，设定tablewidget行数
        {
            if(all_hotel.value(hotel[i])->returnState()==Pass)
            {
                nRow1++;
            }
            else
            {
                nRow2++;
            }
        }
    }
    ui->HotelPass->setRowCount(nRow1);
    ui->HotelUnPass->setRowCount(nRow2);
    for(int i=0;i<Size;i++)
    {
        if(all_hotel.value(hotel[i])->returnOwner()==Owner)
        {
            if(all_hotel.value(hotel[i])->returnState()==Pass)
            {
                for(int k=0;k<7;k++)
                {
                    QTableWidgetItem *item = new QTableWidgetItem;
                    item->setText(all_hotel.value(hotel[i])->returnInfo(k));
                    item->setTextAlignment(Qt::AlignHCenter);
                    ui->HotelPass->setItem(j1, k, item);
                }
                j1++;
            }
            else
            {
                for(int k=0;k<7;k++)
                {
                    QTableWidgetItem *item = new QTableWidgetItem;
                    item->setText(all_hotel.value(hotel[i])->returnInfo(k));
                    item->setTextAlignment(Qt::AlignHCenter);
                    ui->HotelUnPass->setItem(j2, k, item);
                }
                j2++;
            }
        }
   }
}

void MainWindow::showManagerInfo() const//显示雇佣的经理
{
    ui->seeManager->clear();
    QString Id=loginuser->returnId();
    int Num=all_people.value(Id)->returnManagerNumber();
    QString* manager=all_people.value(Id)->getManager();
    for(int i=0;i<Num;i++)
    {
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(manager[i]);
        item->setTextAlignment(Qt::AlignHCenter);
        ui->seeManager->addItem(item);
    }
}
void MainWindow::show()
{
    QMainWindow::show();
    showManagerInfo();
    showHotelInfo();
}

void MainWindow::on_pushButton_3_clicked()//查看房间
{
    allofRoom *allroom =new allofRoom(this);
    QList<QTableWidgetSelectionRange>ranges=ui->HotelPass->selectedRanges();
    int Row=ranges.at(0).topRow();
    QString Id=ui->HotelPass->item(Row,0)->text();
    selecthotel=all_hotel.value(Id);
    allroom->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    QString Id=loginuser->returnId();
    QString newmanager=ui->newManager->text();
    if(!all_people.contains(newmanager)
            ||all_people.value(newmanager)->returnType()!=hotelmanager//判断用户是否已经存在及是否是经理
            ||now_manager.contains(newmanager))
    {
        QMessageBox::QMessageBox::warning(this, tr("警告！"),tr("该用户不存在！"), QMessageBox::Yes);
    }
    else
    {
        QMessageBox::QMessageBox::information(this, tr("提示！"),tr("添加成功！"), QMessageBox::Yes);
        all_people.value(Id)->addManager(newmanager);
        now_manager.insert(newmanager,Id);
        new_manager[new_manager_number]=newmanager;
        its_boss[new_manager_number]=Id;
        new_manager_number++;
        this->show();
    }

}

void MainWindow::on_HotelPass_cellClicked(int row, int column)
{
    ui->pushButton_3->setEnabled(true);
}

void MainWindow::on_HotelPass_itemSelectionChanged()
{
    if(ui->HotelPass->selectedItems().size()==0)
    {
        ui->pushButton_3->setEnabled(false);
    }
}

//数据保存
void MainWindow::closeEvent(QCloseEvent *event)
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
