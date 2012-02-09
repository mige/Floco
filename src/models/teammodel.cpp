#include "teammodel.h"

TeamModel::TeamModel(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
    setTable("team");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();

    setHeaderData(0, Qt::Horizontal, tr("ID"));
    setHeaderData(1, Qt::Horizontal, tr("Name"));
}
