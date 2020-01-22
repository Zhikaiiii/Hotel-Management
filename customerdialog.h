#ifndef CUSTOMERDIALOG_H
#define CUSTOMERDIALOG_H

#include <QDialog>

namespace Ui {
class customerDialog;
}

class customerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit customerDialog(QWidget *parent = 0);
    ~customerDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::customerDialog *ui;
};

#endif // CUSTOMERDIALOG_H
