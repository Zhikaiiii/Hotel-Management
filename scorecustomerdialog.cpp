#include "scorecustomerdialog.h"
#include "ui_scorecustomerdialog.h"
#include "mainwindow_manager.h"
#include "data.h"
ScoreCustomerDialog::ScoreCustomerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScoreCustomerDialog)
{
    ui->setupUi(this);
    QPixmap pixmap = QPixmap(":/images/5.png").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
}

ScoreCustomerDialog::~ScoreCustomerDialog()
{
    delete ui;
}

void ScoreCustomerDialog::on_pushButton_clicked()//投诉顾客
{
    selectorder->scoreCustomer(1);
    this->close();
}

void ScoreCustomerDialog::on_pushButton_2_clicked()//返回
{
    this->close();
}
