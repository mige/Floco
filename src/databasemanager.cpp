#include "databasemanager.h"

#include <QDebug>
#include <QDir>

DatabaseManager* DatabaseManager::instance = NULL;

DatabaseManager::DatabaseManager(){ }


DatabaseManager* DatabaseManager::getInstance()
{
    if(instance == NULL)
        instance = new DatabaseManager();
    return instance;
}

bool DatabaseManager::open(QString filePath, QString fileName)
{
    QDir dir(filePath);
    if(!dir.exists(filePath))
        dir.mkpath(filePath);

    QString dbFile = filePath + QDir::separator() + fileName;

    // Find QSqlite driver
    db = QSqlDatabase::addDatabase("QSQLITE");

    // Store database file
    db.setDatabaseName(dbFile);
    qDebug("DB File: "+dbFile.toAscii());

    return db.open();
}

void DatabaseManager::close()
{
    db.close();
}

QSqlError DatabaseManager::lastError()
{
    return db.lastError();
}
