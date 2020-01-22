#ifndef ADDROOMDIALOG_H
#define ADDROOMDIALOG_H

#include <QDialog>

namespace Ui {
class addRoomDialog;
}

class addRoomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addRoomDialog(QWidget *parent = 0);
    ~addRoomDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_comboBox_type_currentIndexChanged(int index);

private:
    Ui::addRoomDialog *ui;
};

#endif // ADDROOMDIALOG_H
