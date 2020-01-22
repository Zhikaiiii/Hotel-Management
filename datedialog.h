#ifndef DATEDIALOG_H
#define DATEDIALOG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class DateDialog;
}

class DateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DateDialog(QWidget *parent = 0);
    ~DateDialog();
    void show();
    void closeEvent(QCloseEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_pushButton_2_clicked();

    void on_calendarWidget2_clicked(const QDate &date);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::DateDialog *ui;
};

#endif // DATEDIALOG_H
