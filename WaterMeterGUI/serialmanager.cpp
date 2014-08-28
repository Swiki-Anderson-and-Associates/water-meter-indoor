#include "serialmanager.h"

#include <QMessageBox>

SerialManager::SerialManager()
{
    settings = new SettingsDialog;
    connect(this, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
}

SerialManager::~SerialManager()
{
    closePort();
    delete settings;
}

void SerialManager::showSettings()
{
    settings->show();
}

QString SerialManager::openPort()
{
    SettingsDialog::Settings p = settings->settings();
    setPortName(p.name);
    if (open(QIODevice::ReadWrite)) {
        if (setBaudRate(p.baudRate)
                && setDataBits(p.dataBits)
                && setParity(p.parity)
                && setStopBits(p.stopBits)
                && setFlowControl(p.flowControl)) {
            return tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl);

        } else {
            close();
            return tr("Open error");
        }
    } else {

        return tr("Configure error");  // should be "Open error", please check them
    }
}

void SerialManager::closePort()
{
    close();
}

void SerialManager::writeData(QString text)
{
    write(text.toLocal8Bit());
}

QByteArray SerialManager::readData()        // as of right now, this function is pointless, but could be useful
{
    QByteArray data = readAll();
    return data;
}

void SerialManager::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        closePort();
    }
}
