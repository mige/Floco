#include "databasemanager.h"

#include <QDebug>
#include <QDir>
#include <QSqlQuery>

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

    if(!db.open()) return false;

    QFile file(":/db/db.sql");
    file.open(QIODevice::ReadOnly);

    QTextStream stream(&file);

    QString queryString = stream.readAll();

    file.close();

    QStringList queryList = queryString.split(";");

    QSqlQuery query;

    for(int i = 0; i < queryList.size(); i++)
    {
        if(!query.exec(queryList.at(i))) return true; // předpokládá se stav, kdy databáze už je vytvořena
    }

    return true;
}

void DatabaseManager::close()
{
    db.close();
}

QSqlError DatabaseManager::lastError()
{
    return db.lastError();
}
