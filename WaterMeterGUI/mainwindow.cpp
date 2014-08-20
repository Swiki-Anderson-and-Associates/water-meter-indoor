#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtSerialPort/QSerialPort>
#include <QFileDialog>
#include <QScrollBar>
#include <QList>
#include <QDateTime>
#include <QTime>

//#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setup Log File
    logFile.setFileName("log.txt");
    logFile.open(QIODevice::Append);
    log.setDevice(&logFile);
    // TODO: make log files refresh monthly

    // Setup Console
    QPalette p = ui->consoleTextDisplay->palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    ui->consoleTextDisplay->setEnabled(false);
    ui->consoleTextDisplay->setReadOnly(true);
    ui->consoleTextDisplay->setPalette(p);
    ui->consoleDisconnectButton->setEnabled(false);

    // Setup Database
    db = new DatabaseManager;
    ui->databaseBrowseButton->setEnabled(true);
    ui->databaseConnectButton->setEnabled(false);
    ui->databaseDisconnectButton->setEnabled(false);
    ui->databasePathLineEdit->setEnabled(true);

    // Setup Serial Port
    serial = new SerialManager;

    // Setup Plot UI
    ui->plotStartTimeLabel->setVisible(false);
    ui->plotStartTimeEdit->setVisible(false);
    ui->plotEndTimeLabel->setVisible(false);
    ui->plotEndTimeEdit->setVisible(false);

    // Setup Plot
    ui->plotPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

    // Create Auto-Update Timer
    updateTimer = new QTimer(this);
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(refreshControlPanel()));
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(plotUpdate()));
    updateTimer->start(30000);                                                        // update every thirty seconds

    // Create connection timeout timer
    //connectionTimer = new QTimer(this);             // TODO: figure out this and finish it
    //connect()

    // Connect Console Signals and Slots
    connect(ui->consoleSettingsButton, SIGNAL(clicked()), serial, SLOT(showSettings()));
    connect(ui->consoleConnectButton,SIGNAL(clicked()),this,SLOT(openSerialPort()));
    connect(ui->consoleDisconnectButton,SIGNAL(clicked()),this,SLOT(closeSerialPort()));
    connect(serial,SIGNAL(readyRead()),this,SLOT(readSerialData()));

    // Connect Control Signals and Slots
    connect(ui->controlResetSystemButton,SIGNAL(clicked()),this,SLOT(sendResetCommand()));
    connect(ui->controlForceClosedButton,SIGNAL(clicked()),this,SLOT(sendCloseValveCommand()));
    connect(ui->controlForceOpenButton,SIGNAL(clicked()),this,SLOT(sendOpenValveCommand()));
    connect(ui->controlReadLeakConditionButton,SIGNAL(clicked()),this,SLOT(sendReportLeakCommand()));
    connect(ui->controlReadValvePositionButton,SIGNAL(clicked()),this,SLOT(sendReportValveCommand()));
    connect(ui->controlReadLogButton,SIGNAL(clicked()),this,SLOT(sendReportLogCommand()));
    connect(ui->controlClearLogButton,SIGNAL(clicked()),this,SLOT(sendClearLogCommand()));
    connect(ui->controlClearLeakConditionButton,SIGNAL(clicked()),this,SLOT(sendResetLeakCommand()));
    connect(ui->controlAutoModeButton,SIGNAL(clicked()),this,SLOT(setAutomaticValveControl()));
    ui->controlTab->setEnabled(false);
    // TODO: add autoswitching for mode buttons

    // Connect Database Signals and Slots
    connect(ui->databaseConnectButton,SIGNAL(clicked()),this,SLOT(databaseOpen()));
    connect(ui->databaseDisconnectButton,SIGNAL(clicked()),this,SLOT(databaseClose()));
    connect(ui->databaseBrowseButton,SIGNAL(clicked()),this,SLOT(databaseFileBrowse()));
    connect(ui->databaseNewDBButton,SIGNAL(clicked()),this,SLOT(databaseNewDB()));

    //Connect Plot Signals and Slots
    connect(ui->plotPeriodComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(plotToggleDateTimeBoxes(int)));
    connect(ui->plotRefreshButton,SIGNAL(clicked()),this,SLOT(plotUpdate()));

    plotUpdate();
    refreshControlPanel();
}

MainWindow::~MainWindow()
{
    closeSerialPort();
    databaseClose();
    logFile.flush();
    logFile.close();
    delete ui;
}
\
void MainWindow::openSerialPort()
{ 
    ui->statusBar->showMessage(serial->openPort());
    ui->consoleDisconnectButton->setEnabled(true);
    ui->consoleConnectButton->setEnabled(false);
    ui->consoleTextDisplay->setEnabled(true);
    ui->consoleSettingsButton->setEnabled(false);
    ui->controlTab->setEnabled(true);
}

void MainWindow::closeSerialPort()
{
    serial->closePort();
    ui->statusBar->showMessage(tr("Disconnected"));
    ui->consoleDisconnectButton->setEnabled(false);
    ui->consoleConnectButton->setEnabled(true);
    ui->consoleTextDisplay->setEnabled(false);
    ui->consoleSettingsButton->setEnabled(true);
    ui->controlTab->setEnabled(false);
}

void MainWindow::writeConsole(QString text)
{
    ui->consoleTextDisplay->setTextColor(Qt::green);
    ui->consoleTextDisplay->insertPlainText(text);
}

void MainWindow::readSerialData()
{
    QByteArray data;
    while (serial->canReadLine())
    {
         data = serial->readLine(1024);
         ui->consoleTextDisplay->setTextColor(Qt::magenta);
         ui->consoleTextDisplay->insertPlainText(data);
         QScrollBar *sb = ui->consoleTextDisplay->verticalScrollBar();
         sb->setValue(sb->maximum());
         processLine(QString::fromUtf8(data));
    }
    plotUpdate();
    refreshControlPanel();
    ui->statusBar->showMessage("Transmission Received");
    connectionTimer->start(300000);                             // notify user if no info recieved for 5 mins
}

void MainWindow::processLine(QString dataString)
{
    log << dataString;
    static bool inLog;
    bool inHeader = false;
    if (dataString.contains("Gallon Log"))
    {
        inLog = true;
        inHeader = true;
     }
    else if (dataString.contains("End Log"))
    {
         inLog = false;
    }
    else if (inHeader == false)
    {
        QStringList stringList;
        stringList = dataString.split('\t');
        if (inLog)
        {
            if (!dataString.contains("Empty"))
            {
                if (stringList.length() >=3 )
                {
                    QDateTime dateTime = QDateTime::fromString(stringList[0],"MM/dd/yyyy HH:mm:ss");
                    dateTime.setTimeSpec(Qt::UTC);
                    qint32 unixTime = dateTime.toTime_t();
                    db->logGallon(unixTime,stringList[2].toInt());
                }
            }
        }
        else
        {
            QDateTime dateTime = QDateTime::fromString(stringList[0],"MM/dd/yyyy HH:mm:ss");
            qint32 unixTime = dateTime.toTime_t();
            if (stringList[1].contains("Valve"))
            {
                db->logValve(unixTime,stringList[2].toUtf8());
            }
            if (stringList[1].contains("Leak"))
            {
                db->logLeak(unixTime,stringList[2].toUtf8());
            }
        }
    }
    // TODO: Add handling for improper data format
}

void MainWindow::connectionTimeout()
{
    ui->statusBar->showMessage("Error: Connection Lost");
}

void MainWindow::refreshControlPanel()
{
    QDateTime now = QDateTime::currentDateTime();
    QTime dayStart = QTime::fromMSecsSinceStartOfDay(0);
    QDateTime thisMorning = now;
    thisMorning.setTime(dayStart);
    if (db->isOpen())
    {
        if (db->lastLeak().contains("No leaks"))
        {
            ui->controlLeakConditionLabel->setText("NONE");
        }
        else
        {
            ui->controlLeakConditionLabel->setText("LEAK");
        }
        ui->controlValvePositionLabel->setText(db->lastValve());
        ui->controlGallonsTodayLCD->display(db->numGallonsBetween(thisMorning.toTime_t(),now.toTime_t()));        // TODO: check this, not sure if its working right
    }
    else
    {
        ui->statusBar->showMessage("No database connection.");
    }
}

void MainWindow::sendResetCommand()
{
    serial->writeData("r");
    ui->controlValvePositionLabel->setText("Open");
    ui->controlLeakConditionLabel->setText("None");
}

void MainWindow::sendCloseValveCommand()
{
    serial->writeData("c");
    ui->controlValvePositionLabel->setText("Closed");
}

void MainWindow::sendOpenValveCommand()
{
    serial->writeData("o");
    ui->controlValvePositionLabel->setText("Open");
}

void MainWindow::setAutomaticValveControl()
{
    // TODO: add automatic control function
}

void MainWindow::sendReportLeakCommand()
{
    serial->writeData("l");
}

void MainWindow::sendReportValveCommand()
{
    serial->writeData("v");
}

void MainWindow::sendReportLogCommand()
{
    serial->writeData("h");
}

void MainWindow::sendClearLogCommand()
{
    serial->writeData("q");
}

void MainWindow::sendResetLeakCommand()
{
    serial->writeData("k");
    ui->controlLeakConditionLabel->setText("None");
}

void MainWindow::databaseOpen()
{
    db->openDB(ui->databasePathLineEdit->text());
    ui->databaseBrowseButton->setEnabled(false);
    ui->databaseNewDBButton->setEnabled(false);
    ui->databaseConnectButton->setEnabled(false);
    ui->databaseDisconnectButton->setEnabled(true);
    ui->databasePathLineEdit->setEnabled(false);
    refreshControlPanel();
    ui->statusBar->showMessage("Connected to database.");
}

void MainWindow::databaseClose()
{
    db->closeDB();
    ui->databaseBrowseButton->setEnabled(true);
    ui->databaseNewDBButton->setEnabled(true);
    ui->databaseConnectButton->setEnabled(true);
    ui->databaseDisconnectButton->setEnabled(false);
    ui->databasePathLineEdit->setEnabled(true);
}

void MainWindow::databaseFileBrowse()
{
    QString path = QFileDialog::getOpenFileName(this,tr("Locate Database"),"",tr("SQLite Database (*.sqlite)"));
    ui->databasePathLineEdit->setText(path);
    if (!path.isEmpty())
    {
        ui->databaseConnectButton->setEnabled(true);
    }
    else
    {
        ui->databaseConnectButton->setEnabled(false);
    }
}

void MainWindow::databaseNewDB()
{
    QString path = QFileDialog::getSaveFileName(this,tr("New Database"),"",tr("SQLite Database (*.sqlite)"));
    ui->databasePathLineEdit->setText(path);
    if (!path.isEmpty())
    {
        ui->databaseConnectButton->setEnabled(true);
    }
    else
    {
        ui->databaseConnectButton->setEnabled(false);
    }
}

void MainWindow::plotToggleDateTimeBoxes(int index)
{
    if (index == ui->plotPeriodComboBox->findText("Custom"))
    {
        ui->plotStartTimeLabel->setVisible(true);
        ui->plotStartTimeEdit->setVisible(true);
        ui->plotEndTimeLabel->setVisible(true);
        ui->plotEndTimeEdit->setVisible(true);
    }
    else
    {
        ui->plotStartTimeLabel->setVisible(false);
        ui->plotStartTimeEdit->setVisible(false);
        ui->plotEndTimeLabel->setVisible(false);
        ui->plotEndTimeEdit->setVisible(false);
    }
}

void MainWindow::plotUpdate()
{
    if (db->isOpen())
    {
        ui->plotPlot->clearItems();
        ui->plotPlot->clearPlottables();
        ui->plotPlot->clearGraphs();
        QCPBars *gallons = new QCPBars(ui->plotPlot->xAxis, ui->plotPlot->yAxis);
        ui->plotPlot->addPlottable(gallons);
        QPen pen;
        pen.setWidthF(1.2);
        gallons->setName("Gallons Used");
        pen.setColor(QColor(20, 40, 200));
        gallons->setPen(pen);
        gallons->setBrush(QColor(20, 40, 200, 50));
        ui->plotPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
        ui->plotPlot->xAxis->setAutoTickStep(false);
        ui->plotPlot->xAxis->setAutoSubTicks(false);
       // ui->plotPlot->yAxis->setAutoTickStep(false);
       // ui->plotPlot->yAxis->setAutoSubTicks(false);

        QDateTime now = QDateTime::currentDateTime();
        unsigned int tnow = now.toTime_t();
        unsigned int start, end, resolution, ngal, ngalmax, ngalsum, tprev;
        unsigned long tsum;
        QVector<double> barPos, gallonsData;
        ngalmax = 0;
        ngalsum = 0;

        switch (ui->plotPeriodComboBox->currentIndex())
        {
        case 0:     // last hour
            start = tnow-3600;
            end = tnow;
            resolution = 60;
            tprev = start;
            for (unsigned int t = start+resolution; t<=end; t+=resolution)
            {
                ngal = db->numGallonsBetween(tprev,t-1);
                ngalsum += ngal;
                if (ngal > ngalmax)
                {
                    ngalmax = ngal;
                }
                gallonsData  << ngal;
                tsum = t+tprev;
                barPos << tsum/2;
                tprev = t;
            }
            gallons->setData(barPos,gallonsData);
            gallons->setWidth(50);
            ui->plotPlot->xAxis->setDateTimeFormat("HH:mm");
            ui->plotPlot->xAxis->setTickStep(60*10); // 10 minutes
            ui->plotPlot->xAxis->setSubTickCount(9);
            ui->plotPlot->xAxis->setLabel("Time");
            ui->plotPlot->yAxis->setLabel("Gallons Used By Minute");
            break;
        case 1:     // last day
            start = tnow-(3600*24);
            end = tnow;
            resolution = 3600;
            tprev = start;
            for (unsigned int t = start+resolution; t<=end; t+=resolution)
            {
                ngal = db->numGallonsBetween(tprev,t-1);
                ngalsum += ngal;
                if (ngal > ngalmax)
                {
                    ngalmax = ngal;
                }
                gallonsData  << ngal;
                tsum = t+tprev;
                barPos << tsum/2;
                tprev = t;
            }
            gallons->setData(barPos,gallonsData);
            gallons->setWidth(50);
            ui->plotPlot->xAxis->setDateTimeFormat("h AP");
            ui->plotPlot->xAxis->setTickStep(3600*3); // 1 hour
            ui->plotPlot->xAxis->setSubTickCount(5);
            ui->plotPlot->xAxis->setLabel("Time");
            ui->plotPlot->yAxis->setLabel("Gallons Used By Hour");
            break;
        case 2:     // last 3 days
            start = tnow-(3600*24*3);
            end = tnow;
            resolution = 3600;
            tprev = start;
            for (unsigned int t = start+resolution; t<=end; t+=resolution)
            {
                ngal = db->numGallonsBetween(tprev,t-1);
                ngalsum += ngal;
                if (ngal > ngalmax)
                {
                    ngalmax = ngal;
                }
                gallonsData  << ngal;
                tsum = t+tprev;
                barPos << tsum/2;
                tprev = t;
            }
            gallons->setData(barPos,gallonsData);
            gallons->setWidth(50);
            ui->plotPlot->xAxis->setDateTimeFormat("MM/dd");
            ui->plotPlot->xAxis->setTickStep(3600*24); // 1 day
            ui->plotPlot->xAxis->setSubTickCount(24);
            ui->plotPlot->xAxis->setLabel("Time");
            ui->plotPlot->yAxis->setLabel("Gallons Used By Hour");
            break;
        case 3:     // last week                // TODO: fix week and month so that they start at midnight
            start = tnow-(3600*24*7);
            end = tnow;
            resolution = 3600*24;
            tprev = start;
            for (unsigned int t = start+resolution; t<=end; t+=resolution)
            {
                ngal = db->numGallonsBetween(tprev,t-1);
                ngalsum += ngal;
                if (ngal > ngalmax)
                {
                    ngalmax = ngal;
                }
                gallonsData  << ngal;
                tsum = t+tprev;
                barPos << tsum/2;
                tprev = t;
            }
            gallons->setData(barPos,gallonsData);
            gallons->setWidth(50);
            ui->plotPlot->xAxis->setDateTimeFormat("MM/dd");
            ui->plotPlot->xAxis->setTickStep(3600*24); // 1 day
            ui->plotPlot->xAxis->setSubTickCount(23);
            ui->plotPlot->xAxis->setLabel("Time");
            ui->plotPlot->yAxis->setLabel("Gallons Used By Day");
            break;
        case 4:     // last month
            start = tnow-(3600*24*30);              // TODO: fix to account for different amounts of days
            end = tnow;
            resolution = 3600*24;
            tprev = start;
            for (unsigned int t = start+resolution; t<=end; t+=resolution)
            {
                ngal = db->numGallonsBetween(tprev,t-1);
                ngalsum += ngal;
                if (ngal > ngalmax)
                {
                    ngalmax = ngal;
                }
                gallonsData  << ngal;
                tsum = t+tprev;
                barPos << tsum/2;
                tprev = t;
            }
            gallons->setData(barPos,gallonsData);
            gallons->setWidth(50);
            ui->plotPlot->xAxis->setDateTimeFormat("MM/dd");
            ui->plotPlot->xAxis->setTickStep(3600*24*7); // 1 day
            ui->plotPlot->xAxis->setSubTickCount(6);
            ui->plotPlot->xAxis->setLabel("Time");
            ui->plotPlot->yAxis->setLabel("Gallons Used By Day");
            break;
        case 5:     // last year
            start = tnow-(3600*24*365);              // TODO: fix to account for different leap years
            end = tnow;
            resolution = 3600*24*30;
            tprev = start;
            for (unsigned int t = start+resolution; t<=end; t+=resolution)
            {
                ngal = db->numGallonsBetween(tprev,t-1);
                ngalsum += ngal;
                if (ngal > ngalmax)
                {
                    ngalmax = ngal;
                }
                gallonsData  << ngal;
                tsum = t+tprev;
                barPos << tsum/2;
                tprev = t;
            }
            gallons->setData(barPos,gallonsData);
            gallons->setWidth(50);
            ui->plotPlot->xAxis->setDateTimeFormat("MMM yy");
            ui->plotPlot->xAxis->setTickStep(3600*24*30); // 1 month            // TODO: fix to account for different month lengths
            ui->plotPlot->xAxis->setSubTickCount(0);
            ui->plotPlot->xAxis->setLabel("Time");
            ui->plotPlot->yAxis->setLabel("Gallons Used By Month");
            break;
        case 6:     // custom                           // TODO: fix to allow custom time periods
            /*
            start = ui->plotStartTimeEdit->dateTime();
            end = ui->plotEndTimeEdit->dateTime();*/
            break;
        }

        //ui->plotPlot->yAxis->setTickStep(1);
        //ui->plotPlot->yAxis->setSubTickCount(0);
        ui->plotPlot->xAxis->setRange(start,end);
        ui->plotPlot->yAxis->setRange(0,ngalmax);
        ui->plotPlot->rescaleAxes();
        ui->plotPlot->replot();
        ui->plotTotalGallonsLCDNumber->display(int(ngalsum));
    }
    else
    {
        ui->statusBar->showMessage("No database connection.");
    }
}
