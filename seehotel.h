#ifndef SEEHOTEL_H
#define SEEHOTEL_H
#include <QMainWindow>

namespace Ui {
class seeHotel;
}

class seeHotel : public QMainWindow
{
    Q_OBJECT

public:
    explicit seeHotel(QWidget *parent = 0);
    ~seeHotel();
    void show();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_roomType_currentIndexChanged(int index);

    void on_roomnumber_currentIndexChanged(int index);

private:
    Ui::seeHotel *ui;
};

#endif // SEEHOTEL_H
