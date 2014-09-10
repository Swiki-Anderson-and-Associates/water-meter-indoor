#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtSerialPort/QSerialPort>
#include <QFileDialog>
#include <QScrollBar>
#include <QList>
#include <QDateTime>
#include <QTime>
#include <QDate>
#include <QString>
#include <QtSql>
#include <QSqlError>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setup Log File
    QDateTime now = QDateTime::currentDateTime();
    logFile.setFileName("log" + now.toString("MMM_yyyy") + ".txt");
    //logFile.setFileName("log.txt");
    logFile.open(QIODevice::Append);
    log.setDevice(&logFile);
    // TODO: separate hex and interpreted log files
    // (Done)TODO: make log files refresh monthly

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
    connectionTimer = new QTimer(this);             //(Done)TODO: figure out this and finish it
    connect(connectionTimer,SIGNAL(timeout()),this,SLOT(connectionTimeout()));  // in SLOT readSerialData,  "timer-start()" will restart the timer every time.
    connectionTimer->start(300000);
    connectionTimer->setSingleShot(1); // if once disconnected, other functions will be disabled.  Please use single-shot

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
         //processLine(QString::fromUtf8(data));
         processLine(data);
         //TODO: Get rid of String, then use byteArray directly.
    }
    plotUpdate();
    refreshControlPanel();
    ui->statusBar->showMessage("Transmission Received");
    connectionTimer->start(300000);                            // notify user if no info recieved for 5 mins
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
                    if (!dateTime.isValid())
                    {
                        ui->statusBar->showMessage("Improper date format.");
                    }
                    dateTime.setTimeSpec(Qt::UTC);
                    qint32 unixTime = dateTime.toTime_t();
                    db->logGallon(unixTime,stringList[2].toInt());
                }
            }
        }
        else
        {
            QDateTime dateTime = QDateTime::fromString(stringList[0],"MM/dd/yyyy HH:mm:ss");
            if (!dateTime.isValid())
            {
                ui->statusBar->showMessage("Improper date format.");
            }
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
    // (Done)TODO: Add handling for improper data format
}

void MainWindow::processLine(QByteArray data)
{

    log << QString::fromUtf8(data);  // (check) if log file need to be added annotations or just data_string?
    static bool inLog;
    bool inHeader = false;
    if ((data[0]|0x0) == 0x04)  // if (dataString.contains("Gallon Log"))
    {
        inLog = true;
        inHeader = true;
     }
    else if ((data[0]|0x0) == 0x02)  // else if (dataString.contains("End Log"))
    {
         inLog = false;
    }
    else if (inHeader == false)      // This guard seems not necessary.  The main problem is that if "Gallon Log" or "End Log", nothing will be done in this function.
    {
        if (inLog)
        {
            if(!data.isEmpty())  //  if (!dataString.contains("Empty")) //
            {
                if (data.size() >= 5)      //if (stringList.length() >=3 )
                {
                    qint32 unixTime = (data[1]<<24)|(data[2]<<16)|(data[3]<<8)|(data[4]);
                    db->logGallon(unixTime,1);//db->logGallon(unixTime,stringList[2].toInt());  //(Check) if the stringList[2] is gallon amount
                }
            }
        }
        else
        {
            qint32 unixTime = (data[1]<<24)|(data[2]<<16)|(data[3]<<8)|(data[4]);
            if((data[0] >> 4) == 0x1) //if (stringList[1].contains("Valve"))
            {
                //db->logValve(unixTime,stringList[2].toUtf8());
                db->logValve(unixTime,data[0]);   // (check) if it is OK that one byte (two nibble) was added in logValve.
            }
            if ((data[0]>>4) == 0x2 )//if (stringList[1].contains("Leak"))
            {
                db->logLeak(unixTime,data[0]); //db->logLeak(unixTime,stringList[2].toUtf8());
            }
        }
    }
}

void MainWindow::connectionTimeout()
{
    ui->statusBar->showMessage("Error: Connection Lost");
}

void MainWindow::refreshControlPanel()
{
    QDateTime now = QDateTime::currentDateTime();
    //QDateTime now = QDateTime::fromString("2014/06/17 17:00:00", "yyyy/MM/dd hh:mm:ss");
    //qDebug() << now.toString();
    QTime dayStart = QTime::fromMSecsSinceStartOfDay(0);
    QDateTime thisMorning = now;
    thisMorning.setTime(dayStart);
    //if (db->isOpen())
    if (db->db.isOpen())
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
        ui->controlGallonsTodayLCD->display(db->numGallonsBetween(thisMorning.toTime_t(),now.toTime_t()));   // (Checked)TODO: check this, not sure if its working right
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
    if (db->db.isOpen())
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
        //QDate nowd = QDate::currentDate();
        //QTime nowt = QTime::currentTime();
        QDateTime tdatetime;  // The QDatetime for variable t;  used as temp variale sometimes
        unsigned int secsofDay = now.time().msecsSinceStartOfDay()/1000;
        unsigned int tnow = now.toTime_t();
        unsigned int start, end, resolution, ngal, ngalmax, ngalsum, tprev;
        unsigned long tsum;
        QVector<double> barPos, gallonsData,tickPos;
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
        case 3:     // last week              //(Done)TODO: fix week and month so that they start at midnight
            start = tnow-(3600*24*7+secsofDay);
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
            //start = tnow-((3600*24*now.date().daysInMonth())+secsofDay);          //(Done)TODO: fix to account for different amounts of days
            tdatetime = now.addMonths(-1);
            start = tdatetime.toTime_t() - secsofDay;
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
            ui->plotPlot->xAxis->setTickStep(3600*24*7); // 1 week
            ui->plotPlot->xAxis->setSubTickCount(6);
            ui->plotPlot->xAxis->setLabel("Time");
            ui->plotPlot->yAxis->setLabel("Gallons Used By Day");
            break;
        case 5:     // last year
            //start = tnow-(3600*24*now.date().daysInYear());       //(Done)TODO: fix to account for different leap years
            tdatetime = now.addYears(-1);
            start = tdatetime.toTime_t() -(3600*24*(tdatetime.date().day()-1) + secsofDay);  // Start at the midnight of the first day in month
            end = tnow;
            tdatetime.setTime_t(start);
            resolution = 3600*24*tdatetime.date().daysInMonth();
            tprev = start;
            tickPos << start;
            for (unsigned int t = start+resolution; t <= end ; t+=resolution)
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
                tdatetime.setTime_t(t);
                resolution = 3600*24*tdatetime.date().daysInMonth();
                tickPos << t;
            }
            gallons->setData(barPos,gallonsData);
            gallons->setWidth(50);
            ui->plotPlot->xAxis->setDateTimeFormat("MMM yy");
            //ui->plotPlot->xAxis->setTickStep(3600*24*now.date().daysInMonth()); // 1 month    //(Done)TODO: fix to account for different month lengths
            ui->plotPlot->xAxis->setAutoTicks(false);
            ui->plotPlot->xAxis->setTickVector(barPos);
            ui->plotPlot->xAxis->setSubTickCount(0);
            ui->plotPlot->xAxis->setLabel("Time");
            ui->plotPlot->yAxis->setLabel("Gallons Used By Month");
            break;
        case 6:     // custom                           // (Done)TODO: fix to allow custom time periods
            /*
            start = ui->plotStartTimeEdit->dateTime();
            end = ui->plotEndTimeEdit->dateTime();*/
            tdatetime = ui->plotStartTimeEdit->dateTime();
            start = tdatetime.toTime_t();
            tdatetime = ui->plotEndTimeEdit->dateTime();
            end = tdatetime.toTime_t();
            if (end < start) ui->statusBar->showMessage("Incorrect custom time periods.");
            else{
            if ((end - start) > 3600*24*90)   // >3 months, resolution is month lenght (dynamic)
            {
                tdatetime.setTime_t(start);
                resolution = 3600*24*tdatetime.date().daysInMonth();
                tprev = start;
                tickPos << start;
                for (unsigned int t = start+resolution; t <= end + 3600*24*30 ; t+=resolution)
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
                    tdatetime.setTime_t(t);
                    resolution = 3600*24*tdatetime.date().daysInMonth();
                    tickPos << t;
                }
                gallons->setData(barPos,gallonsData);
                gallons->setWidth(50);
                ui->plotPlot->xAxis->setDateTimeFormat("MMM yy");
                ui->plotPlot->xAxis->setAutoTicks(false);
                ui->plotPlot->xAxis->setTickVector(tickPos);
                ui->plotPlot->xAxis->setSubTickCount(0);
                ui->plotPlot->xAxis->setLabel("Time");
                ui->plotPlot->yAxis->setLabel("Gallons Used By Month");
            }
            else  // <3 months, resolution is static
            {
                if ((end - start) > 3600*24*28)  //3months >= span >4 weeks
                {
                    resolution = 3600*24;
                    ui->plotPlot->xAxis->setDateTimeFormat("MM/dd");
                    ui->plotPlot->xAxis->setTickStep(3600*24*7); // 1 week
                    ui->plotPlot->xAxis->setSubTickCount(6);
                    ui->plotPlot->xAxis->setLabel("Time");
                    ui->plotPlot->yAxis->setLabel("Gallons Used By Day");
                }
                else
                {
                    if ((end - start) > 3600*24*5)  //4weeks >=span >5days
                    {
                        resolution = 3600*24;
                        ui->plotPlot->xAxis->setDateTimeFormat("MM/dd");
                        ui->plotPlot->xAxis->setTickStep(3600*24); // 1 day
                        ui->plotPlot->xAxis->setSubTickCount(23);
                        ui->plotPlot->xAxis->setLabel("Time");
                        ui->plotPlot->yAxis->setLabel("Gallons Used By Day");
                    }
                    else
                    {
                        if((end - start) > 3600*24*2)  //5days >= span > 2days
                        {
                            resolution = 3600;
                            ui->plotPlot->xAxis->setDateTimeFormat("MM/dd");
                            ui->plotPlot->xAxis->setTickStep(3600*24); // 1 day
                            ui->plotPlot->xAxis->setSubTickCount(24);
                            ui->plotPlot->xAxis->setLabel("Time");
                            ui->plotPlot->yAxis->setLabel("Gallons Used By Hour");
                        }
                        else
                        {
                            if ((end - start) > 3600*10)  //2days >= span >10hours
                            {
                                resolution = 3600;
                                ui->plotPlot->xAxis->setDateTimeFormat("h AP");
                                ui->plotPlot->xAxis->setTickStep(3600*3); // 3 hour
                                ui->plotPlot->xAxis->setSubTickCount(5);
                                ui->plotPlot->xAxis->setLabel("Time");
                                ui->plotPlot->yAxis->setLabel("Gallons Used By Hour");
                            }
                            else  // <10hours
                            {
                                resolution = 60;
                                ui->plotPlot->xAxis->setDateTimeFormat("HH:mm");
                                ui->plotPlot->xAxis->setTickStep(60*10); // 10 minutes
                                ui->plotPlot->xAxis->setSubTickCount(9);
                                ui->plotPlot->xAxis->setLabel("Time");
                                ui->plotPlot->yAxis->setLabel("Gallons Used By Minute");
                            }
                        }
                    }
                }
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
            }
            }
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
