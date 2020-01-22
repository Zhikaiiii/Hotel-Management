#include "mainwindow.h"
#include "mainwindow_customer.h"
#include "mainwindow_manager.h"
#include "mainwindow_supervisor.h"
#include <QApplication>
#include "logindiag.h"
#include "data.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    createConnection();
    hotel_createConnection();
    order_createConnection();
    LoginDiag dlg;
    dlg.show();
    return a.exec();
}
