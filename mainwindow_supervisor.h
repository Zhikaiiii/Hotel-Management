#ifndef MAINWINDOW_SUPERVISOR_H
#define MAINWINDOW_SUPERVISOR_H

#include <QMainWindow>
#include<QListWidgetItem>
#include <QCloseEvent>

namespace Ui {
class MainWindow_supervisor;
}

class MainWindow_supervisor : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_supervisor(QWidget *parent = 0);
    ~MainWindow_supervisor();
    void showHotelInfo() const;
    void show();
    void closeEvent(QCloseEvent *event);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_hotelUnpass_cellClicked(int row, int column);

    void on_hotelPass_cellClicked(int row, int column);

    void on_hotelUnpass_itemSelectionChanged();

    void on_hotelPass_itemSelectionChanged();



    void on_pushButton_5_clicked();

private:
    Ui::MainWindow_supervisor *ui;
};

#endif // MAINWINDOW_SUPERVISOR_H
