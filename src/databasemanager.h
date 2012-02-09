#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    static DatabaseManager* getInstance();
    bool                    open(QString filePath, QString fileName);
    void                    close();
    QSqlError               lastError();

protected:
    DatabaseManager();

private:
    static DatabaseManager *instance;
    QSqlDatabase            db;
};

#endif // DATABASEMANAGER_H
