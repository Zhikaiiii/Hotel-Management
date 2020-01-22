#ifndef MAINWINDOW_CUSTOMER_ORDER_H
#define MAINWINDOW_CUSTOMER_ORDER_H

#include <QMainWindow>
#include <QCloseEvent>
namespace Ui {
class MainWindow_customer_order;
}

class MainWindow_customer_order : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_customer_order(QWidget *parent = 0);
    ~MainWindow_customer_order();
    void SetItem(int i,int j);
    void showOrderInfo();
    void show();
    void showDetailed();
    void closeEvent(QCloseEvent *event);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_OrderInfo_cellClicked(int row, int column);

    void on_OrderInfo_itemSelectionChanged();

private:
    Ui::MainWindow_customer_order *ui;
};

#endif // MAINWINDOW_CUSTOMER_ORDER_H
