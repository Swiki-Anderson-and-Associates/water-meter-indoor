#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include "settingsdialog.h"

#include <QtSerialPort/QSerialPort>

class SerialManager : public QSerialPort
{
    Q_OBJECT

public:
    SerialManager();
    ~SerialManager();

private slots:
    void handleError(QSerialPort::SerialPortError error);

public slots:
    void showSettings();
    QString openPort();
    void closePort();
    //void writeData(QString text);
    void writeData(QByteArray byte);
    QByteArray readData();

private:
    SettingsDialog *settings;
};

#endif // SERIALMANAGER_H
