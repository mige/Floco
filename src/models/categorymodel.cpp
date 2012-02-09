#include "categorymodel.h"

#include <QSqlField>
#include <QSqlRecord>

CategoryModel::CategoryModel(QObject *parent) :
    QSqlTableModel(parent)
{
    setTable("team_category");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();

    setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    setHeaderData(3, Qt::Horizontal, QObject::tr("Max age"));
}

QVariant CategoryModel::data(const QModelIndex &index, int role) const
 {
     QVariant value = QSqlQueryModel::data(index, role);
     if (value.isValid() && role == Qt::DisplayRole)
         if (index.column() == 3)
         {
             if(value.toInt() == 100)
                 return QVariant(tr("adult"));
         }

     return value;
 }

QList<QString> CategoryModel::categoryList()
{
    QList<QString> categoryList;
    for(int i = 0; i < rowCount(); i++)
        categoryList << record(i).field("name").value().toString();
    return categoryList;
}
