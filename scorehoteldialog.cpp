#include "scorehoteldialog.h"
#include "ui_scorehoteldialog.h"
#include "data.h"
#include "mainwindow_customer_order.h"
#include <QMessageBox>

ScoreHotelDialog::ScoreHotelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScoreHotelDialog)
{
    ui->setupUi(this);
    QPixmap pixmap = QPixmap(":/images/2.png").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
    ui->pushButton->setStyleSheet("background:transparent");
    ui->pushButton_2->setStyleSheet("background:transparent");
    ui->pushButton_3->setStyleSheet("background:transparent");
    ui->pushButton_4->setStyleSheet("background:transparent");
    ui->pushButton_5->setStyleSheet("background:transparent");
    ui->pushButton->setIcon(QPixmap(":/images/star.png"));
    ui->pushButton->setIconSize(QSize(30,30));
    ui->pushButton_2->setIcon(QPixmap(":/images/star.png"));
    ui->pushButton_2->setIconSize(QSize(30,30));
    ui->pushButton_3->setIcon(QPixmap(":/images/star.png"));
    ui->pushButton_3->setIconSize(QSize(30,30));
    ui->pushButton_4->setIcon(QPixmap(":/images/star.png"));
    ui->pushButton_4->setIconSize(QSize(30,30));
    ui->pushButton_5->setIcon(QPixmap(":/images/star.png"));
    ui->pushButton_5->setIconSize(QSize(30,30));
}

ScoreHotelDialog::~ScoreHotelDialog()
{
    delete ui;
}

void ScoreHotelDialog::on_pushButton_7_clicked()
{
    this->close();
}

void ScoreHotelDialog::on_pushButton_6_clicked()
{
    if(selectorder->returnHscore()==0)
    {
        QMessageBox::QMessageBox::warning(this, tr("警告！"),tr("您还未选定评分！"), QMessageBox::Yes);
    }
    else
    {
        QMessageBox::QMessageBox::information(this, tr("提示！"),tr("评分成功！"), QMessageBox::Yes);
        this->close();
    }
}
//1分
void ScoreHotelDialog::on_pushButton_clicked()
{
    selectorder->scoreHotel(1);
    ui->pushButton->setIcon(QPixmap(":/images/star1.png"));
    ui->pushButton->setIconSize(QSize(30,30));
    ui->pushButton_2->setIcon(QPixmap(":/images/star.png"));
    ui->pushButton_2->setIconSize(QSize(30,30));
    ui->pushButton_3->setIcon(QPixmap(":/images/star.png"));
    ui->pushButton_3->setIconSize(QSize(30,30));
    ui->pushButton_4->setIcon(QPixmap(":/images/star.png"));
    ui->pushButton_4->setIconSize(QSize(30,30));
    ui->pushButton_5->setIcon(QPixmap(":/images/star.png"));
    ui->pushButton_5->setIconSize(QSize(30,30));
}

//2分
void ScoreHotelDialog::on_pushButton_2_clicked()
{
    selectorder->scoreHotel(2);
    ui->pushButton->setIcon(QPixmap(":/images/star1.png"));
    ui->pushButton->setIconSize(QSize(30,30));
    ui->pushButton_2->setIcon(QPixmap(":/images/star1.png"));
    ui->pushButton_2->setIconSize(QSize(30,30));
    ui->pushButton_3->setIcon(QPixmap(":/images/star.png"));
    ui->pushButton_3->setIconSize(QSize(30,30));
    ui->pushButton_4->setIcon(QPixmap(":/images/star.png"));
    ui->pushButton_4->setIconSize(QSize(30,30));
    ui->pushButton_5->setIcon(QPixmap(":/images/star.png"));
    ui->pushButton_5->setIconSize(QSize(30,30));
}

//3分
void ScoreHotelDialog::on_pushButton_3_clicked()
{
    selectorder->scoreHotel(3);
    ui->pushButton->setIcon(QPixmap(":/images/star1.png"));
    ui->pushButton->setIconSize(QSize(30,30));
    ui->pushButton_2->setIcon(QPixmap(":/images/star1.png"));
    ui->pushButton_2->setIconSize(QSize(30,30));
    ui->pushButton_3->setIcon(QPixmap(":/images/star1.png"));
    ui->pushButton_3->setIconSize(QSize(30,30));
    ui->pushButton_4->setIcon(QPixmap(":/images/star.png"));
    ui->pushButton_4->setIconSize(QSize(30,30));
    ui->pushButton_5->setIcon(QPixmap(":/images/star.png"));
    ui->pushButton_5->setIconSize(QSize(30,30));
}

//4分
void ScoreHotelDialog::on_pushButton_4_clicked()
{
    selectorder->scoreHotel(4);
    ui->pushButton->setIcon(QPixmap(":/images/star1.png"));
    ui->pushButton->setIconSize(QSize(30,30));
    ui->pushButton_2->setIcon(QPixmap(":/images/star1.png"));
    ui->pushButton_2->setIconSize(QSize(30,30));
    ui->pushButton_3->setIcon(QPixmap(":/images/star1.png"));
    ui->pushButton_3->setIconSize(QSize(30,30));
    ui->pushButton_4->setIcon(QPixmap(":/images/star1.png"));
    ui->pushButton_4->setIconSize(QSize(30,30));
    ui->pushButton_5->setIcon(QPixmap(":/images/star.png"));
    ui->pushButton_5->setIconSize(QSize(30,30));
}

//5分
void ScoreHotelDialog::on_pushButton_5_clicked()
{
    ui->pushButton->setIcon(QPixmap(":/images/star1.png"));
    ui->pushButton->setIconSize(QSize(30,30));
    ui->pushButton_2->setIcon(QPixmap(":/images/star1.png"));
    ui->pushButton_2->setIconSize(QSize(30,30));
    ui->pushButton_3->setIcon(QPixmap(":/images/star1.png"));
    ui->pushButton_3->setIconSize(QSize(30,30));
    ui->pushButton_4->setIcon(QPixmap(":/images/star1.png"));
    ui->pushButton_4->setIconSize(QSize(30,30));
    ui->pushButton_5->setIcon(QPixmap(":/images/star1.png"));
    ui->pushButton_5->setIconSize(QSize(30,30));
    selectorder->scoreHotel(5);
}
