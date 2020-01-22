#ifndef SCOREHOTELDIALOG_H
#define SCOREHOTELDIALOG_H

#include <QDialog>

namespace Ui {
class ScoreHotelDialog;
}

class ScoreHotelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScoreHotelDialog(QWidget *parent = 0);
    ~ScoreHotelDialog();

private slots:
    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::ScoreHotelDialog *ui;
};

#endif // SCOREHOTELDIALOG_H
