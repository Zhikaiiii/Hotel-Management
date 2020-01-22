#ifndef MAINWINDOW_CUSTOMER_H
#define MAINWINDOW_CUSTOMER_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QCloseEvent>
namespace Ui {
class MainWindow_customer;
}

class MainWindow_customer : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_customer(QWidget *parent = 0);
    ~MainWindow_customer();
    void showHotelInfo();
    void show();
    void setItem(int i,int j);
    void closeEvent(QCloseEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_RoomType_currentIndexChanged(int index);

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_hotelLookup_itemClicked(QTableWidgetItem *item);

    void on_hotelLookup_itemSelectionChanged();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow_customer *ui;
};

#endif // MAINWINDOW_CUSTOMER_H
