#-------------------------------------------------
#
# Project created by QtCreator 2018-07-18T20:12:34
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = login1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    logindiag.cpp \
    registerdiag.cpp \
    mainwindow_manager.cpp \
    mainwindow_customer.cpp \
    hotel.cpp \
    addhoteldialog.cpp \
    addroomdialog.cpp \
    allofroom.cpp \
    mainwindow_supervisor.cpp \
    data.cpp \
    order.cpp \
    customerdialog.cpp \
    datedialog.cpp \
    mainwindow_customer_order.cpp \
    seehotel.cpp \
    people.cpp \
    date.cpp \
    scorecustomerdialog.cpp \
    scorehoteldialog.cpp \
    mainwindow_supervisor_customer.cpp

HEADERS += \
        mainwindow.h \
    logindiag.h \
    registerdiag.h \
    room.h \
    mainwindow_manager.h \
    mainwindow_customer.h \
    hotel.h \
    addhoteldialog.h \
    addroomdialog.h \
    allofroom.h \
    mainwindow_supervisor.h \
    people.h \
    data.h \
    order.h \
    customerdialog.h \
    datedialog.h \
    mainwindow_customer_order.h \
    seehotel.h \
    date.h \
    scorecustomerdialog.h \
    scorehoteldialog.h \
    mainwindow_supervisor_customer.h

FORMS += \
        mainwindow.ui \
    logindiag.ui \
    registerdiag.ui \
    mainwindow_manager.ui \
    mainwindow_customer.ui \
    addhoteldialog.ui \
    addroomdialog.ui \
    allofroom.ui \
    mainwindow_supervisor.ui \
    customerdialog.ui \
    datedialog.ui \
    mainwindow_customer_order.ui \
    seehotel.ui \
    scorecustomerdialog.ui \
    scorehoteldialog.ui \
    mainwindow_supervisor_customer.ui

RESOURCES += \
    resource.qrc
