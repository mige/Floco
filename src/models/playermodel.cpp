#include "playermodel.h"

PlayerModel::PlayerModel(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
    setTable("player");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();

    setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    setHeaderData(1, Qt::Horizontal, QObject::tr("Firstname"));
    setHeaderData(2, Qt::Horizontal, QObject::tr("Surname"));
    setHeaderData(3, Qt::Horizontal, QObject::tr("Day of birth"));
    setHeaderData(4, Qt::Horizontal, QObject::tr("Address"));
    setHeaderData(5, Qt::Horizontal, QObject::tr("E-mail"));
    setHeaderData(6, Qt::Horizontal, QObject::tr("Phone"));
    setHeaderData(7, Qt::Horizontal, QObject::tr("Number"));
    setHeaderData(8, Qt::Horizontal, QObject::tr("Photo"));
    setHeaderData(9, Qt::Horizontal, QObject::tr("Post"));
}
