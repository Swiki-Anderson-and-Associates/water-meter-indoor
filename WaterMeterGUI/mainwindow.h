#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "databasemanager.h"
#include "serialmanager.h"

#include <QtCore/QtGlobal>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QFile>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openSerialPort();
    void closeSerialPort();
    void writeConsole(QString text);
    void readSerialData();
    void processLine(QString dataString);
    void connectionTimeout();
    void refreshControlPanel();
    void sendResetCommand();
    void sendCloseValveCommand();
    void sendOpenValveCommand();
    void sendReportLeakCommand();
    void sendReportValveCommand();
    void sendReportLogCommand();
    void sendClearLogCommand();
    void sendResetLeakCommand();
    void setAutomaticValveControl();
    void databaseOpen();
    void databaseClose();
    void databaseFileBrowse();
    void databaseNewDB();
    void plotToggleDateTimeBoxes(int index);
    void plotUpdate();

private:
    Ui::MainWindow *ui;
    DatabaseManager *db;
    SerialManager *serial;
    QFile logFile;
    QTextStream log;
    QTimer *updateTimer;
    QTimer *connectionTimer;
};

#endif // MAINWINDOW_H
