#ifndef MAINWINDOW_SUPERVISOR_CUSTOMER_H
#define MAINWINDOW_SUPERVISOR_CUSTOMER_H

#include <QMainWindow>
#include<QListWidgetItem>
#include <QCloseEvent>
namespace Ui {
class MainWindow_supervisor_customer;
}

class MainWindow_supervisor_customer : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_supervisor_customer(QWidget *parent = 0);
    ~MainWindow_supervisor_customer();
    void showCustomer();
    void show();
    void closeEvent(QCloseEvent *event);

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_6_clicked();

    void on_customerPass_itemClicked(QListWidgetItem *item);

    void on_customerUnpass_itemClicked(QListWidgetItem *item);

    void on_customerPass_itemSelectionChanged();

    void on_customerUnpass_itemSelectionChanged();

    void on_pushButton_clicked();

private:
    Ui::MainWindow_supervisor_customer *ui;

};

#endif // MAINWINDOW_SUPERVISOR_CUSTOMER_H
