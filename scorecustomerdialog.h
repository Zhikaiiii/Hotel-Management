#ifndef SCORECUSTOMERDIALOG_H
#define SCORECUSTOMERDIALOG_H

#include <QDialog>

namespace Ui {
class ScoreCustomerDialog;
}

class ScoreCustomerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScoreCustomerDialog(QWidget *parent = 0);
    ~ScoreCustomerDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ScoreCustomerDialog *ui;
};

#endif // SCORECUSTOMERDIALOG_H
