#ifndef LOGINDIAG_H
#define LOGINDIAG_H
#include "mainwindow.h"
#include "mainwindow_supervisor.h"
#include "mainwindow_manager.h"
#include "mainwindow_customer.h"
#include "customerdialog.h"
#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class LoginDiag;
}

class LoginDiag : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDiag(QWidget *parent = 0);
    ~LoginDiag();
    MainWindow *hhotel;
    MainWindow_supervisor *ssupervisor;
    MainWindow_manager *mmanager;
    customerDialog *ccustomer;
    void closeEvent(QCloseEvent *event);


private slots:
    void on_ExitBtn_clicked();

    void on_LoginBtn_clicked();

    void on_pwdLineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_RegBtn_clicked();

private:
    Ui::LoginDiag *ui;
};

#endif // LOGINDIAG_H
