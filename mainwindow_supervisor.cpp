#include "mainwindow_supervisor.h"
#include "ui_mainwindow_supervisor.h"
#include <QDebug>
#include <QMessageBox>
#include "data.h"
#include "logindiag.h"
#include "mainwindow_supervisor_customer.h"
MainWindow_supervisor::MainWindow_supervisor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_supervisor)
{
    ui->setupUi(this);
    //界面美化
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    QPixmap pixmap = QPixmap(":/images/2.png").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
    ui->hotelPass->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgba(0,0,0,0)};");
    ui->hotelPass->verticalHeader()->hide();
    ui->hotelUnpass->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgba(0,0,0,0)};");
    ui->hotelUnpass->verticalHeader()->hide();
}

MainWindow_supervisor::~MainWindow_supervisor()
{
    delete ui;
}

void MainWindow_supervisor::showHotelInfo() const//显示酒店信息
{
    int j1=0;
    int j2=0;
    int nRow1=0;
    int nRow2=0;
    int Size=all_hotel.size();
    for(int i=0;i<Size;i++)
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
    ui->hotelPass->setRowCount(nRow1);
    ui->hotelUnpass->setRowCount(nRow2);
    for(int i=0;i<Size;i++)
    {
        if(all_hotel.value(hotel[i])->returnState()==Pass)
        {
            for(int k=0;k<7;k++)
            {
                QTableWidgetItem *item = new QTableWidgetItem;
                item->setText(all_hotel.value(hotel[i])->returnInfo(k));
                item->setTextAlignment(Qt::AlignHCenter);
                ui->hotelPass->setItem(j1, k, item);
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
                ui->hotelUnpass->setItem(j2, k, item);
            }
            j2++;
        }
    }
}

void MainWindow_supervisor::show()
{
    QMainWindow::show();
    showHotelInfo();
}
//改变酒店状态
void MainWindow_supervisor::on_pushButton_clicked()
{
    QList<QTableWidgetSelectionRange>ranges=ui->hotelUnpass->selectedRanges();
    int Row=ranges.at(0).topRow();
    QString Id=ui->hotelUnpass->item(Row,0)->text();
    all_hotel.value(Id)->changeState(Pass);
    this->show();
}

void MainWindow_supervisor::on_pushButton_2_clicked()
{
    QList<QTableWidgetSelectionRange>ranges=ui->hotelUnpass->selectedRanges();
    int Row=ranges.at(0).topRow();
    QString Id=ui->hotelUnpass->item(Row,0)->text();
    all_hotel.value(Id)->changeState(Reject);
    this->show();
}

void MainWindow_supervisor::on_pushButton_3_clicked()
{
    QList<QTableWidgetSelectionRange>ranges=ui->hotelPass->selectedRanges();
    int Row=ranges.at(0).topRow();
    QString Id=ui->hotelPass->item(Row,0)->text();
    all_hotel.value(Id)->changeState(Waiting);
    this->show();
}

void MainWindow_supervisor::on_pushButton_6_clicked()//返回登录界面
{
    LoginDiag *log=new LoginDiag(this);
    this->hide();
    log->show();
}


void MainWindow_supervisor::on_pushButton_4_clicked()//显示酒店评价
{
    QList<QTableWidgetSelectionRange>ranges=ui->hotelPass->selectedRanges();
    int Row=ranges.at(0).topRow();
    QString Id=ui->hotelPass->item(Row,0)->text();
    ui->scoreaverage->setText(QString::number(all_hotel.value(Id)->calScore()));
    ui->score1->setText(QString::number(all_hotel.value(Id)->returnScore(0)));
    ui->score2->setText(QString::number(all_hotel.value(Id)->returnScore(1)));
    ui->score3->setText(QString::number(all_hotel.value(Id)->returnScore(2)));
    ui->score4->setText(QString::number(all_hotel.value(Id)->returnScore(3)));
    ui->score5->setText(QString::number(all_hotel.value(Id)->returnScore(4)));
}

//管理顾客界面
void MainWindow_supervisor::on_pushButton_5_clicked()
{
    MainWindow_supervisor_customer *mainwindow=new MainWindow_supervisor_customer(this);
    this->hide();
    mainwindow->show();
}

//程序容错性设置
void MainWindow_supervisor::on_hotelUnpass_cellClicked(int row, int column)
{
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
}

void MainWindow_supervisor::on_hotelPass_cellClicked(int row, int column)
{
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
}

void MainWindow_supervisor::on_hotelUnpass_itemSelectionChanged()
{
    if(ui->hotelUnpass->selectedItems().size()==0)
    {
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
    }
}

void MainWindow_supervisor::on_hotelPass_itemSelectionChanged()
{
    if(ui->hotelPass->selectedItems().size()==0)
    {
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
    }
}

//保存数据
void MainWindow_supervisor::closeEvent(QCloseEvent *event)
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
