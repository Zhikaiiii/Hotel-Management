#ifndef MAINWINDOW_MANAGER_H
#define MAINWINDOW_MANAGER_H

#include <QMainWindow>
#include <QCloseEvent>
namespace Ui {
class MainWindow_manager;
}

class MainWindow_manager : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_manager(QWidget *parent = 0);
    ~MainWindow_manager();
    void showHotelInfo()const;
    void showOrderInfo();
    void show();
    void SetItem(int i,int j);
    void showDetailed();//显示一个订单的具体信息并进行操作
    void closeEvent(QCloseEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_hotel_cellClicked(int row, int column);

    void on_order_cellClicked(int row, int column);

    void on_hotel_itemSelectionChanged();

    void on_order_itemSelectionChanged();

private:
    Ui::MainWindow_manager *ui;
};

#endif // MAINWINDOW_MANAGER_H
