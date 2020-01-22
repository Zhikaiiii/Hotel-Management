#ifndef ADDHOTELDIALOG_H
#define ADDHOTELDIALOG_H

#include <QDialog>

namespace Ui {
class addHotelDialog;
}

class addHotelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addHotelDialog(QWidget *parent = 0);
    ~addHotelDialog();

private slots:
    void on_pushButton_regi_clicked();

    void on_pushButton_exit_clicked();

private:
    Ui::addHotelDialog *ui;
};

#endif // ADDHOTELDIALOG_H
