#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>

/**
 * @brief The DatabaseManager class provides database connection.
 * If the database does not exist, create a new database in user's home directory.
 */
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
