#-------------------------------------------------
#
# Project created by QtCreator 2014-05-02T13:13:58
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport printsupport

TARGET = WaterMeterGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingsdialog.cpp \
    databasemanager.cpp \
    serialmanager.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    settingsdialog.h \
    databasemanager.h \
    serialmanager.h \
    qcustomplot.h

FORMS    += mainwindow.ui \
    settingsdialog.ui
