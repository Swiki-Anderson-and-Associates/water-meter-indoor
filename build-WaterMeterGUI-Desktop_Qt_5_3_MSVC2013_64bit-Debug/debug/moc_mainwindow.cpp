/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../WaterMeterGUI/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[27];
    char stringdata[430];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 14),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 15),
QT_MOC_LITERAL(4, 43, 12),
QT_MOC_LITERAL(5, 56, 4),
QT_MOC_LITERAL(6, 61, 14),
QT_MOC_LITERAL(7, 76, 11),
QT_MOC_LITERAL(8, 88, 10),
QT_MOC_LITERAL(9, 99, 17),
QT_MOC_LITERAL(10, 117, 19),
QT_MOC_LITERAL(11, 137, 16),
QT_MOC_LITERAL(12, 154, 21),
QT_MOC_LITERAL(13, 176, 20),
QT_MOC_LITERAL(14, 197, 21),
QT_MOC_LITERAL(15, 219, 22),
QT_MOC_LITERAL(16, 242, 20),
QT_MOC_LITERAL(17, 263, 19),
QT_MOC_LITERAL(18, 283, 20),
QT_MOC_LITERAL(19, 304, 24),
QT_MOC_LITERAL(20, 329, 12),
QT_MOC_LITERAL(21, 342, 13),
QT_MOC_LITERAL(22, 356, 18),
QT_MOC_LITERAL(23, 375, 13),
QT_MOC_LITERAL(24, 389, 23),
QT_MOC_LITERAL(25, 413, 5),
QT_MOC_LITERAL(26, 419, 10)
    },
    "MainWindow\0openSerialPort\0\0closeSerialPort\0"
    "writeConsole\0text\0readSerialData\0"
    "processLine\0dataString\0connectionTimeout\0"
    "refreshControlPanel\0sendResetCommand\0"
    "sendCloseValveCommand\0sendOpenValveCommand\0"
    "sendReportLeakCommand\0sendReportValveCommand\0"
    "sendReportLogCommand\0sendClearLogCommand\0"
    "sendResetLeakCommand\0setAutomaticValveControl\0"
    "databaseOpen\0databaseClose\0"
    "databaseFileBrowse\0databaseNewDB\0"
    "plotToggleDateTimeBoxes\0index\0plotUpdate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  124,    2, 0x08 /* Private */,
       3,    0,  125,    2, 0x08 /* Private */,
       4,    1,  126,    2, 0x08 /* Private */,
       6,    0,  129,    2, 0x08 /* Private */,
       7,    1,  130,    2, 0x08 /* Private */,
       9,    0,  133,    2, 0x08 /* Private */,
      10,    0,  134,    2, 0x08 /* Private */,
      11,    0,  135,    2, 0x08 /* Private */,
      12,    0,  136,    2, 0x08 /* Private */,
      13,    0,  137,    2, 0x08 /* Private */,
      14,    0,  138,    2, 0x08 /* Private */,
      15,    0,  139,    2, 0x08 /* Private */,
      16,    0,  140,    2, 0x08 /* Private */,
      17,    0,  141,    2, 0x08 /* Private */,
      18,    0,  142,    2, 0x08 /* Private */,
      19,    0,  143,    2, 0x08 /* Private */,
      20,    0,  144,    2, 0x08 /* Private */,
      21,    0,  145,    2, 0x08 /* Private */,
      22,    0,  146,    2, 0x08 /* Private */,
      23,    0,  147,    2, 0x08 /* Private */,
      24,    1,  148,    2, 0x08 /* Private */,
      26,    0,  151,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->openSerialPort(); break;
        case 1: _t->closeSerialPort(); break;
        case 2: _t->writeConsole((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->readSerialData(); break;
        case 4: _t->processLine((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->connectionTimeout(); break;
        case 6: _t->refreshControlPanel(); break;
        case 7: _t->sendResetCommand(); break;
        case 8: _t->sendCloseValveCommand(); break;
        case 9: _t->sendOpenValveCommand(); break;
        case 10: _t->sendReportLeakCommand(); break;
        case 11: _t->sendReportValveCommand(); break;
        case 12: _t->sendReportLogCommand(); break;
        case 13: _t->sendClearLogCommand(); break;
        case 14: _t->sendResetLeakCommand(); break;
        case 15: _t->setAutomaticValveControl(); break;
        case 16: _t->databaseOpen(); break;
        case 17: _t->databaseClose(); break;
        case 18: _t->databaseFileBrowse(); break;
        case 19: _t->databaseNewDB(); break;
        case 20: _t->plotToggleDateTimeBoxes((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->plotUpdate(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 22;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
