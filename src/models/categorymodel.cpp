#include "categorymodel.h"

#include <QSqlField>
#include <QSqlRecord>

/**
 * @brief Creates a category model and set header data.
 * @param parent Parent object.
 */
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

/**
 * @brief Gets the data from the model.
 * @param index Model index.
 * @param role If set Qt::DisplayRole, replace in 3. column 100 with adult.
 * @return Returns the data for the given role for the item referred to by the index.
 */
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

/**
 * @brief Gets the list of categories from the model.
 * @return List of categories.
 */
QList<QString> CategoryModel::categoryList()
{
    QList<QString> categoryList;
    for(int i = 0; i < rowCount(); i++)
        categoryList << record(i).field("name").value().toString();
    return categoryList;
}
