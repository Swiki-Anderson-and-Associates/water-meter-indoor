#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();
    bool openDB(QString path);
    void closeDB();
    void setupTables();
    void logGallon(int time, int gallon);
    void logValve(int time, QString position);
    void logLeak(int time, QString leak);
    QString lastLeak();
    QString lastValve();
    QSqlError lastError();
    int numGallonsBetween(int start, int end);

private:
    QSqlDatabase db;
    QString dbDirectory;
};

#endif // DATABASEMANAGER_H
