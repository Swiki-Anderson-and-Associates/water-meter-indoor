#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

<<<<<<< HEAD
//class DatabaseManager : public QSqlDatabase
=======
>>>>>>> origin/joye
class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();
    bool openDB(QString path);
    void closeDB();
    void setupTables();
    void logGallon(qint32 time, qint32 gallon);
    void logValve(qint32  time, QString position);
    void logLeak(qint32 time, QString leak);
    QString lastLeak();
    QString lastValve();
    QSqlError lastError();
    int numGallonsBetween(qint32 start, qint32 end);
<<<<<<< HEAD
    QSqlDatabase db;
=======
    QSqlDatabase db;                                        // TODO: make this private (encapsulation is good)
>>>>>>> origin/joye

private:

    QString dbDirectory;
};

#endif // DATABASEMANAGER_H
