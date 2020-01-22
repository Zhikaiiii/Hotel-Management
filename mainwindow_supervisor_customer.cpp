#include "mainwindow_supervisor_customer.h"
#include "ui_mainwindow_supervisor_customer.h"
#include <QDebug>
#include <QMessageBox>
#include "data.h"
#include "logindiag.h"
#include "mainwindow_supervisor.h"

MainWindow_supervisor_customer::MainWindow_supervisor_customer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_supervisor_customer)
{
    ui->setupUi(this);
    //界面美化
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_10->setEnabled(false);
    ui->pushButton_8->setEnabled(false);
    ui->pushButton_11->setEnabled(false);
    QPixmap pixmap = QPixmap(":/images/2.png").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
}

MainWindow_supervisor_customer::~MainWindow_supervisor_customer()
{
    delete ui;
}

void MainWindow_supervisor_customer::on_pushButton_5_clicked()//将顾客移入黑名单
{
    QListWidgetItem *item = ui->customerPass->takeItem(ui->customerPass->currentRow());
    QString id=item->text();
    for(int i=0;i<all_people_number;i++)
    {
        if(people[i]==id)
        {
            all_people.value(people[i])->changeState(1);
            break;
        }
    }
    show();
}

void MainWindow_supervisor_customer::on_pushButton_11_clicked()//将顾客从黑名单移除
{
    QListWidgetItem *item = ui->customerUnpass->takeItem(ui->customerUnpass->currentRow());
    QString id=item->text();
    for(int i=0;i<all_people_number;i++)
    {
        if(people[i]==id)
        {
            all_people.value(people[i])->changeState(0);
            break;
        }
    }
    show();
}

//查看顾客订单数及评价
void MainWindow_supervisor_customer::on_pushButton_8_clicked()
{
    QListWidgetItem *item = ui->customerPass->takeItem(ui->customerPass->currentRow());
    QString id=item->text();
    int* a=all_people.value(id)->getOrderNumber();
    ui->ordernumber->setText(QString::number(a[0]));
    ui->badjudgement->setText(QString::number(a[1]));
    showCustomer();
}

void MainWindow_supervisor_customer::on_pushButton_10_clicked()
{
    QListWidgetItem *item = ui->customerUnpass->takeItem(ui->customerUnpass->currentRow());
    QString id=item->text();
    int* a=all_people.value(id)->getOrderNumber();
    ui->ordernumber->setText(QString::number(a[0]));
    ui->badjudgement->setText(QString::number(a[1]));
    showCustomer();
}

void MainWindow_supervisor_customer::on_pushButton_6_clicked()//返回登录界面
{
    LoginDiag *log=new LoginDiag(this);
    this->hide();
    log->show();
}

void MainWindow_supervisor_customer::showCustomer()//显示顾客信息
{
    ui->customerPass->clear();
    ui->customerUnpass->clear();
    for(int i=0;i<all_people_number;i++)
    {
        if(all_people.value(people[i])->returnType()==customer)
        {
            QListWidgetItem *item = new QListWidgetItem;
            item->setText(people[i]);
            item->setTextAlignment(Qt::AlignHCenter);
            if(all_people.value(people[i])->returnState()==0)
            {
                ui->customerPass->addItem(item);
            }
            else
            {
                ui->customerUnpass->addItem(item);
            }
        }
    }
}

void MainWindow_supervisor_customer::show()
{
    QMainWindow::show();
    showCustomer();
}

//程序容错性设置
void MainWindow_supervisor_customer::on_customerPass_itemClicked(QListWidgetItem *item)
{
    ui->pushButton_5->setEnabled(true);
    ui->pushButton_8->setEnabled(true);
}

void MainWindow_supervisor_customer::on_customerUnpass_itemClicked(QListWidgetItem *item)
{
    ui->pushButton_11->setEnabled(true);
    ui->pushButton_10->setEnabled(true);
}

void MainWindow_supervisor_customer::on_customerPass_itemSelectionChanged()
{
    if(ui->customerPass->selectedItems().size()==0)
    {
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_8->setEnabled(false);
    }
}

void MainWindow_supervisor_customer::on_customerUnpass_itemSelectionChanged()
{
    if(ui->customerUnpass->selectedItems().size()==0)
    {
        ui->pushButton_11->setEnabled(false);
        ui->pushButton_10->setEnabled(false);
    }
}

void MainWindow_supervisor_customer::on_pushButton_clicked()//管理酒店页面
{
     MainWindow_supervisor *mainwindow=new MainWindow_supervisor(this);
     this->hide();
     mainwindow->show();
}

void MainWindow_supervisor_customer::closeEvent(QCloseEvent *event)//保存数据
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
