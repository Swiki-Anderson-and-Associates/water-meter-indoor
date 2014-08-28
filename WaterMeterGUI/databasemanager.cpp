#include "databasemanager.h"
#include <QVariant>
#include <QDebug>
#include <QSqlError>
DatabaseManager::DatabaseManager()
{
}

DatabaseManager::~DatabaseManager()
{
    closeDB();
}

bool DatabaseManager::openDB(QString path)
{
    bool ret;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    ret = db.open();
    //setDatabaseName(path);
    //addDatabase("QSQLITE");
    //ret = open();
    setupTables();
    return ret;
}

void DatabaseManager::closeDB()
{
    db.close();
    //close();
}

void DatabaseManager::setupTables()
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS GallonLog(GId INTEGER PRIMARY KEY, Time INTEGER, Gallon INTEGER)");
    query.exec("CREATE TABLE IF NOT EXISTS ValveLog(VId INTEGER PRIMARY KEY, Time INTEGER, Position TEXT)");
    query.exec("CREATE TABLE IF NOT EXISTS LeakLog(LId INTEGER PRIMARY KEY, Time INTEGER, Leak TEXT)");
}

void DatabaseManager::logGallon(qint32 time, qint32 gallon)
{
    QSqlQuery query;
    query.prepare("INSERT INTO GallonLog(Time, Gallon) VALUES(:time, :gallon)");
    query.bindValue(":time",time);
    query.bindValue(":gallon",gallon);
    query.exec();
}

void DatabaseManager::logValve(qint32 time, QString position)
{
    QSqlQuery query;
    query.prepare("INSERT INTO ValveLog(Time, Position) VALUES(:time, :position)");
    query.bindValue(":time",time);
    query.bindValue(":position",position.toLocal8Bit());
    query.exec();
}

void DatabaseManager::logLeak(qint32 time, QString leak)
{
    QSqlQuery query;
    query.prepare("INSERT INTO LeakLog(Time, Leak) VALUES(:time, :leak)");
    query.bindValue(":time",time);
    query.bindValue(":leak",leak.toLocal8Bit());
    query.exec();
}

QString DatabaseManager::lastValve()
{
    QSqlQuery query;
    query.exec("SELECT Position FROM ValveLog WHERE VId = (SELECT MAX(VId) FROM ValveLog)");
    query.next();
    return query.value(0).toString();
}

QString DatabaseManager::lastLeak()
{
    QSqlQuery query;
    query.exec("SELECT Leak FROM LeakLog WHERE LId = (SELECT MAX(LId) FROM LeakLog)");
    query.next();
    return query.value(0).toString();
}

int DatabaseManager::numGallonsBetween(qint32 start, qint32 end)
{
    QSqlQuery query;
    query.prepare("SELECT count(*) FROM GallonLog Where Gallon BETWEEN :s AND :e");
    query.bindValue(":s",start);
    query.bindValue(":e",end);
    query.exec();
    query.next();
    return query.value(0).toInt();
}
