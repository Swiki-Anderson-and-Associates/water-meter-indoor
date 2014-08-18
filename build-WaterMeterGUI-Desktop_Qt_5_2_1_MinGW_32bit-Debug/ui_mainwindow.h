/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConsole;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QTabWidget *tabWidget;
    QWidget *controlTab;
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_6;
    QPushButton *controlReadLogButton;
    QPushButton *controlClearLogButton;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_8;
    QLCDNumber *controlGallonsTodayLCD;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_9;
    QPushButton *controlReadLeakConditionButton;
    QPushButton *controlClearLeakConditionButton;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_10;
    QLabel *controlLeakConditionLabel;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QRadioButton *controlForceOpenButton;
    QRadioButton *controlAutoModeButton;
    QRadioButton *controlForceClosedButton;
    QPushButton *controlReadValvePositionButton;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_4;
    QLabel *controlValvePositionLabel;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_7;
    QPushButton *controlResetSystemButton;
    QWidget *databaseTab;
    QGridLayout *gridLayout_11;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *databasePathLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *databaseNewDBButton;
    QPushButton *databaseBrowseButton;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *databaseConnectButton;
    QPushButton *databaseDisconnectButton;
    QTabWidget *tabWidget_2;
    QWidget *consoleTab;
    QGridLayout *gridLayout_2;
    QTextEdit *consoleTextDisplay;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *consoleSettingsButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *consoleConnectButton;
    QPushButton *consoleDisconnectButton;
    QWidget *plotTab;
    QGridLayout *gridLayout_14;
    QHBoxLayout *horizontalLayout_8;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_12;
    QComboBox *plotPeriodComboBox;
    QDateTimeEdit *plotEndTimeEdit;
    QDateTimeEdit *plotStartTimeEdit;
    QLabel *plotStartTimeLabel;
    QLabel *plotEndTimeLabel;
    QGroupBox *plotMarkersLayout;
    QGridLayout *gridLayout_13;
    QCheckBox *plotValveActuationsCheckBox;
    QCheckBox *plotLeakConditionsCheckBox;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_15;
    QLCDNumber *plotTotalGallonsLCDNumber;
    QPushButton *plotRefreshButton;
    QCustomPlot *plotPlot;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(861, 496);
        actionConsole = new QAction(MainWindow);
        actionConsole->setObjectName(QStringLiteral("actionConsole"));
        actionConsole->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        controlTab = new QWidget();
        controlTab->setObjectName(QStringLiteral("controlTab"));
        controlTab->setLayoutDirection(Qt::LeftToRight);
        gridLayout_5 = new QGridLayout(controlTab);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        groupBox_3 = new QGroupBox(controlTab);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_6 = new QGridLayout(groupBox_3);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        controlReadLogButton = new QPushButton(groupBox_3);
        controlReadLogButton->setObjectName(QStringLiteral("controlReadLogButton"));

        gridLayout_6->addWidget(controlReadLogButton, 0, 0, 1, 1);

        controlClearLogButton = new QPushButton(groupBox_3);
        controlClearLogButton->setObjectName(QStringLiteral("controlClearLogButton"));

        gridLayout_6->addWidget(controlClearLogButton, 1, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_3, 0, 3, 1, 1);

        groupBox_5 = new QGroupBox(controlTab);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        gridLayout_8 = new QGridLayout(groupBox_5);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        controlGallonsTodayLCD = new QLCDNumber(groupBox_5);
        controlGallonsTodayLCD->setObjectName(QStringLiteral("controlGallonsTodayLCD"));
        controlGallonsTodayLCD->setSegmentStyle(QLCDNumber::Flat);

        gridLayout_8->addWidget(controlGallonsTodayLCD, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_5, 0, 1, 1, 2);

        groupBox_6 = new QGroupBox(controlTab);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        gridLayout_9 = new QGridLayout(groupBox_6);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        controlReadLeakConditionButton = new QPushButton(groupBox_6);
        controlReadLeakConditionButton->setObjectName(QStringLiteral("controlReadLeakConditionButton"));

        gridLayout_9->addWidget(controlReadLeakConditionButton, 0, 0, 1, 1);

        controlClearLeakConditionButton = new QPushButton(groupBox_6);
        controlClearLeakConditionButton->setObjectName(QStringLiteral("controlClearLeakConditionButton"));

        gridLayout_9->addWidget(controlClearLeakConditionButton, 1, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_6, 2, 3, 1, 1);

        groupBox_7 = new QGroupBox(controlTab);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        gridLayout_10 = new QGridLayout(groupBox_7);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        controlLeakConditionLabel = new QLabel(groupBox_7);
        controlLeakConditionLabel->setObjectName(QStringLiteral("controlLeakConditionLabel"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        controlLeakConditionLabel->setFont(font);
        controlLeakConditionLabel->setScaledContents(true);
        controlLeakConditionLabel->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(controlLeakConditionLabel, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_7, 2, 1, 1, 2);

        groupBox = new QGroupBox(controlTab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        controlForceOpenButton = new QRadioButton(groupBox);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(controlForceOpenButton);
        controlForceOpenButton->setObjectName(QStringLiteral("controlForceOpenButton"));

        gridLayout_3->addWidget(controlForceOpenButton, 2, 0, 1, 1);

        controlAutoModeButton = new QRadioButton(groupBox);
        buttonGroup->addButton(controlAutoModeButton);
        controlAutoModeButton->setObjectName(QStringLiteral("controlAutoModeButton"));
        controlAutoModeButton->setChecked(true);

        gridLayout_3->addWidget(controlAutoModeButton, 1, 0, 1, 1);

        controlForceClosedButton = new QRadioButton(groupBox);
        buttonGroup->addButton(controlForceClosedButton);
        controlForceClosedButton->setObjectName(QStringLiteral("controlForceClosedButton"));

        gridLayout_3->addWidget(controlForceClosedButton, 3, 0, 1, 1);

        controlReadValvePositionButton = new QPushButton(groupBox);
        controlReadValvePositionButton->setObjectName(QStringLiteral("controlReadValvePositionButton"));

        gridLayout_3->addWidget(controlReadValvePositionButton, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox, 3, 3, 2, 1);

        groupBox_8 = new QGroupBox(controlTab);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        gridLayout_4 = new QGridLayout(groupBox_8);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        controlValvePositionLabel = new QLabel(groupBox_8);
        controlValvePositionLabel->setObjectName(QStringLiteral("controlValvePositionLabel"));
        controlValvePositionLabel->setFont(font);
        controlValvePositionLabel->setScaledContents(true);
        controlValvePositionLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(controlValvePositionLabel, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_8, 3, 1, 1, 2);

        groupBox_4 = new QGroupBox(controlTab);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_7 = new QGridLayout(groupBox_4);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        controlResetSystemButton = new QPushButton(groupBox_4);
        controlResetSystemButton->setObjectName(QStringLiteral("controlResetSystemButton"));

        gridLayout_7->addWidget(controlResetSystemButton, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_4, 4, 1, 1, 2);

        tabWidget->addTab(controlTab, QString());
        databaseTab = new QWidget();
        databaseTab->setObjectName(QStringLiteral("databaseTab"));
        gridLayout_11 = new QGridLayout(databaseTab);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(databaseTab);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        databasePathLineEdit = new QLineEdit(databaseTab);
        databasePathLineEdit->setObjectName(QStringLiteral("databasePathLineEdit"));
        databasePathLineEdit->setReadOnly(true);

        horizontalLayout_4->addWidget(databasePathLineEdit);


        gridLayout_11->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        databaseNewDBButton = new QPushButton(databaseTab);
        databaseNewDBButton->setObjectName(QStringLiteral("databaseNewDBButton"));

        horizontalLayout_3->addWidget(databaseNewDBButton);

        databaseBrowseButton = new QPushButton(databaseTab);
        databaseBrowseButton->setObjectName(QStringLiteral("databaseBrowseButton"));

        horizontalLayout_3->addWidget(databaseBrowseButton);


        gridLayout_11->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        databaseConnectButton = new QPushButton(databaseTab);
        databaseConnectButton->setObjectName(QStringLiteral("databaseConnectButton"));

        horizontalLayout_5->addWidget(databaseConnectButton);

        databaseDisconnectButton = new QPushButton(databaseTab);
        databaseDisconnectButton->setObjectName(QStringLiteral("databaseDisconnectButton"));

        horizontalLayout_5->addWidget(databaseDisconnectButton);


        gridLayout_11->addLayout(horizontalLayout_5, 2, 0, 1, 1);

        tabWidget->addTab(databaseTab, QString());
        splitter->addWidget(tabWidget);
        tabWidget_2 = new QTabWidget(splitter);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        consoleTab = new QWidget();
        consoleTab->setObjectName(QStringLiteral("consoleTab"));
        gridLayout_2 = new QGridLayout(consoleTab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        consoleTextDisplay = new QTextEdit(consoleTab);
        consoleTextDisplay->setObjectName(QStringLiteral("consoleTextDisplay"));

        gridLayout_2->addWidget(consoleTextDisplay, 0, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        consoleSettingsButton = new QPushButton(consoleTab);
        consoleSettingsButton->setObjectName(QStringLiteral("consoleSettingsButton"));

        horizontalLayout_2->addWidget(consoleSettingsButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        consoleConnectButton = new QPushButton(consoleTab);
        consoleConnectButton->setObjectName(QStringLiteral("consoleConnectButton"));

        horizontalLayout_2->addWidget(consoleConnectButton);

        consoleDisconnectButton = new QPushButton(consoleTab);
        consoleDisconnectButton->setObjectName(QStringLiteral("consoleDisconnectButton"));

        horizontalLayout_2->addWidget(consoleDisconnectButton);


        gridLayout_2->addLayout(horizontalLayout_2, 2, 2, 1, 1);

        tabWidget_2->addTab(consoleTab, QString());
        plotTab = new QWidget();
        plotTab->setObjectName(QStringLiteral("plotTab"));
        gridLayout_14 = new QGridLayout(plotTab);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        groupBox_2 = new QGroupBox(plotTab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_12 = new QGridLayout(groupBox_2);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        plotPeriodComboBox = new QComboBox(groupBox_2);
        plotPeriodComboBox->setObjectName(QStringLiteral("plotPeriodComboBox"));

        gridLayout_12->addWidget(plotPeriodComboBox, 0, 0, 1, 2);

        plotEndTimeEdit = new QDateTimeEdit(groupBox_2);
        plotEndTimeEdit->setObjectName(QStringLiteral("plotEndTimeEdit"));

        gridLayout_12->addWidget(plotEndTimeEdit, 2, 1, 1, 1);

        plotStartTimeEdit = new QDateTimeEdit(groupBox_2);
        plotStartTimeEdit->setObjectName(QStringLiteral("plotStartTimeEdit"));

        gridLayout_12->addWidget(plotStartTimeEdit, 1, 1, 1, 1);

        plotStartTimeLabel = new QLabel(groupBox_2);
        plotStartTimeLabel->setObjectName(QStringLiteral("plotStartTimeLabel"));

        gridLayout_12->addWidget(plotStartTimeLabel, 1, 0, 1, 1);

        plotEndTimeLabel = new QLabel(groupBox_2);
        plotEndTimeLabel->setObjectName(QStringLiteral("plotEndTimeLabel"));

        gridLayout_12->addWidget(plotEndTimeLabel, 2, 0, 1, 1);


        horizontalLayout_8->addWidget(groupBox_2);

        plotMarkersLayout = new QGroupBox(plotTab);
        plotMarkersLayout->setObjectName(QStringLiteral("plotMarkersLayout"));
        gridLayout_13 = new QGridLayout(plotMarkersLayout);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        plotValveActuationsCheckBox = new QCheckBox(plotMarkersLayout);
        plotValveActuationsCheckBox->setObjectName(QStringLiteral("plotValveActuationsCheckBox"));

        gridLayout_13->addWidget(plotValveActuationsCheckBox, 0, 0, 1, 1);

        plotLeakConditionsCheckBox = new QCheckBox(plotMarkersLayout);
        plotLeakConditionsCheckBox->setObjectName(QStringLiteral("plotLeakConditionsCheckBox"));

        gridLayout_13->addWidget(plotLeakConditionsCheckBox, 1, 0, 1, 1);


        horizontalLayout_8->addWidget(plotMarkersLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_9 = new QGroupBox(plotTab);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        gridLayout_15 = new QGridLayout(groupBox_9);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        plotTotalGallonsLCDNumber = new QLCDNumber(groupBox_9);
        plotTotalGallonsLCDNumber->setObjectName(QStringLiteral("plotTotalGallonsLCDNumber"));
        plotTotalGallonsLCDNumber->setLineWidth(0);
        plotTotalGallonsLCDNumber->setSmallDecimalPoint(false);
        plotTotalGallonsLCDNumber->setDigitCount(6);
        plotTotalGallonsLCDNumber->setMode(QLCDNumber::Dec);
        plotTotalGallonsLCDNumber->setSegmentStyle(QLCDNumber::Flat);

        gridLayout_15->addWidget(plotTotalGallonsLCDNumber, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_9);

        plotRefreshButton = new QPushButton(plotTab);
        plotRefreshButton->setObjectName(QStringLiteral("plotRefreshButton"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(plotRefreshButton->sizePolicy().hasHeightForWidth());
        plotRefreshButton->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(plotRefreshButton);


        horizontalLayout_8->addLayout(verticalLayout_2);


        gridLayout_14->addLayout(horizontalLayout_8, 1, 0, 1, 2);

        plotPlot = new QCustomPlot(plotTab);
        plotPlot->setObjectName(QStringLiteral("plotPlot"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(plotPlot->sizePolicy().hasHeightForWidth());
        plotPlot->setSizePolicy(sizePolicy1);

        gridLayout_14->addWidget(plotPlot, 0, 0, 1, 2);

        tabWidget_2->addTab(plotTab, QString());
        splitter->addWidget(tabWidget_2);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 861, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuView->addAction(actionConsole);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Water Monitor", 0));
        actionConsole->setText(QApplication::translate("MainWindow", "Console", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Meter Log:", 0));
        controlReadLogButton->setText(QApplication::translate("MainWindow", "Read Log", 0));
        controlClearLogButton->setText(QApplication::translate("MainWindow", "Clear Log", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Gallons Today:", 0));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Leak Cond Control:", 0));
        controlReadLeakConditionButton->setText(QApplication::translate("MainWindow", "Read Leak Cond", 0));
        controlClearLeakConditionButton->setText(QApplication::translate("MainWindow", "Clear Leak Cond", 0));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "Leak Condition:", 0));
        controlLeakConditionLabel->setText(QApplication::translate("MainWindow", "None", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Valve Control:", 0));
        controlForceOpenButton->setText(QApplication::translate("MainWindow", "Force Open", 0));
        controlAutoModeButton->setText(QApplication::translate("MainWindow", "Automatic", 0));
        controlForceClosedButton->setText(QApplication::translate("MainWindow", "Force Closed", 0));
        controlReadValvePositionButton->setText(QApplication::translate("MainWindow", "Read Valve Position", 0));
        groupBox_8->setTitle(QApplication::translate("MainWindow", "Valve Position:", 0));
        controlValvePositionLabel->setText(QApplication::translate("MainWindow", "Open", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "System Control:", 0));
        controlResetSystemButton->setText(QApplication::translate("MainWindow", "Reset System", 0));
        tabWidget->setTabText(tabWidget->indexOf(controlTab), QApplication::translate("MainWindow", "Control", 0));
        label_2->setText(QApplication::translate("MainWindow", "Database Path:", 0));
        databaseNewDBButton->setText(QApplication::translate("MainWindow", "New DB", 0));
        databaseBrowseButton->setText(QApplication::translate("MainWindow", "Browse", 0));
        databaseConnectButton->setText(QApplication::translate("MainWindow", "Connect", 0));
        databaseDisconnectButton->setText(QApplication::translate("MainWindow", "Disconnect", 0));
        tabWidget->setTabText(tabWidget->indexOf(databaseTab), QApplication::translate("MainWindow", "Database", 0));
        consoleSettingsButton->setText(QApplication::translate("MainWindow", "Settings", 0));
        consoleConnectButton->setText(QApplication::translate("MainWindow", "Connect", 0));
        consoleDisconnectButton->setText(QApplication::translate("MainWindow", "Disconnect", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(consoleTab), QApplication::translate("MainWindow", "Console", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Time Period:", 0));
        plotPeriodComboBox->clear();
        plotPeriodComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Past Hour", 0)
         << QApplication::translate("MainWindow", "Past 24 Hours", 0)
         << QApplication::translate("MainWindow", "Past 72 Hours", 0)
         << QApplication::translate("MainWindow", "Past Week", 0)
         << QApplication::translate("MainWindow", "Past Month", 0)
         << QApplication::translate("MainWindow", "Past Year", 0)
         << QApplication::translate("MainWindow", "Custom", 0)
        );
        plotStartTimeLabel->setText(QApplication::translate("MainWindow", "From:", 0));
        plotEndTimeLabel->setText(QApplication::translate("MainWindow", "To:", 0));
        plotMarkersLayout->setTitle(QApplication::translate("MainWindow", "Markers:", 0));
        plotValveActuationsCheckBox->setText(QApplication::translate("MainWindow", "Valve Actuations", 0));
        plotLeakConditionsCheckBox->setText(QApplication::translate("MainWindow", "Leak Conditions", 0));
        groupBox_9->setTitle(QApplication::translate("MainWindow", "Total Gallons:", 0));
        plotRefreshButton->setText(QApplication::translate("MainWindow", "Refresh", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(plotTab), QApplication::translate("MainWindow", "Plot", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
