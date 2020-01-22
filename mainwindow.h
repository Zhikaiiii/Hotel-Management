#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QCloseEvent>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void showManagerInfo()const;
    void showHotelInfo() const;
    void show();
    void closeEvent(QCloseEvent *event);

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_HotelPass_cellClicked(int row, int column);

    void on_HotelPass_itemSelectionChanged();

private:
    Ui::MainWindow *ui;

    //void hide();

};

#endif // MAINWINDOW_H
