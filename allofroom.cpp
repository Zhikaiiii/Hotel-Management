#include "allofroom.h"
#include "ui_allofroom.h"
#include "addroomdialog.h"
#include "mainwindow.h"
#include "data.h"

allofRoom::allofRoom(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::allofRoom)
{
    ui->setupUi(this);
    QPixmap pixmap = QPixmap(":/images/2.png").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );
    ui->seeRoom->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgba(0,0,0,0)};");
    ui->seeRoom->verticalHeader()->hide();
}

allofRoom::~allofRoom()
{
    delete ui;
}

void allofRoom::on_pushButton_clicked()//添加房间
{
    addRoomDialog *dlg =new addRoomDialog(this);
    dlg->show();
}

void allofRoom::on_pushButton_2_clicked()//返回
{
    this->close();
}

void allofRoom::showRoomInfo() const //利用tablewidget显示所有房间信息
{
    QString Id=selecthotel->returnId();
    int nRow=all_hotel.value(Id)->returnTotalRoomNumber();
    int nColumn=ui->seeRoom->columnCount();
    ui->seeRoom->setRowCount(nRow);
    for(int i=0;i<nRow;i++)
    {
        for(int j=0;j<nColumn;j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setText((all_hotel.value(Id)->myroom[i]->returnInfo(j)));
            item->setTextAlignment(Qt::AlignHCenter);
            ui->seeRoom->setItem(i, j, item);
        }
    }
}

void allofRoom::show()//重载show函数
{
    QMainWindow::show();
    showRoomInfo();
}

void allofRoom::on_pushButton_3_clicked()
{
    show();
}
