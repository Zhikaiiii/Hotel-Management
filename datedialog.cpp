#include "datedialog.h"
#include "ui_datedialog.h"
#include "mainwindow_customer.h"
#include "data.h"
#include "date.h"
#include "customerdialog.h"
#include <QMessageBox>

DateDialog::DateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DateDialog)
{
    //界面美化
    ui->setupUi(this);
    ui->pushButton->setStyleSheet("background:transparent");
    ui->pushButton_2->setStyleSheet("background:transparent");
    ui->pushButton->setIcon(QPixmap(":/images/calendar.png"));
    ui->pushButton->setIconSize(QSize(22,22));
    ui->pushButton_2->setIcon(QPixmap(":/images/calendar.png"));
    ui->pushButton_2->setIconSize(QSize(22,22));
    QPixmap pixmap = QPixmap(":/images/4.png").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
}

DateDialog::~DateDialog()
{
    delete ui;
}

void DateDialog::on_pushButton_clicked()
{
    ui->calendarWidget->show();
}

void DateDialog::show()//重载show函数
{
    QDialog::show();
    ui->calendarWidget->close();
    ui->calendarWidget2->close();
}

void DateDialog::on_calendarWidget_clicked(const QDate &date)
{
    QString day1=date.toString("yyyy-MM-dd");
    ui->dayin->setText(day1);
    show();
}

void DateDialog::on_pushButton_2_clicked()
{
    ui->calendarWidget2->show();
}

void DateDialog::on_calendarWidget2_clicked(const QDate &date)
{
    QString day2=date.toString("yyyy-MM-dd");
    ui->dayout->setText(day2);
    show();
}

void DateDialog::on_pushButton_3_clicked()
{
    QString in=ui->dayin->text();
    QString out=ui->dayout->text();
    Date ddayin(in);
    Date ddayout(out);
    if(ddayin>ddayout||ui->dayin->text()==""||ui->dayout->text()=="")//判断日期规范性并传递至主窗口
    {
        QMessageBox::QMessageBox::warning(this, tr("警告！"),tr("日期填写不符合规范！"), QMessageBox::Yes);
    }
    else
    {
        MainWindow_customer *Mainwindow=new MainWindow_customer(this);
        this->hide();
        day_in=ddayin;
        day_out=ddayout;
        Mainwindow->show();

    }
}

void DateDialog::on_pushButton_4_clicked()//返回选择窗口
{
    customerDialog *log=new customerDialog(this);
    this->hide();
    log->show();
}

void DateDialog::closeEvent(QCloseEvent *event)//关闭事件确保保存数据
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
