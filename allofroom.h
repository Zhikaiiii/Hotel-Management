#ifndef ALLOFROOM_H
#define ALLOFROOM_H
#include <QMainWindow>

namespace Ui {
class allofRoom;
}

class allofRoom : public QMainWindow
{
    Q_OBJECT

public:
    explicit allofRoom(QWidget *parent = 0);
    ~allofRoom();
    void showRoomInfo() const;
    void show();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::allofRoom *ui;

};

#endif // ALLOFROOM_H
