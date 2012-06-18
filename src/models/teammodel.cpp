#include "teammodel.h"

#include <QSqlRecord>
#include <QSqlField>

/**
 * @brief Creates a team model and set header data.
 * @param parent Parent object.
 */
TeamModel::TeamModel(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
    setTable("team");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();

    setHeaderData(0, Qt::Horizontal, tr("ID"));
    setHeaderData(1, Qt::Horizontal, tr("Name"));
}

/**
 * @brief Get team position in model.
 * @param teamId Team ID.
 * @return Number of row.
 */
int TeamModel::getPosition(int teamId)
{
    for(int i = 0; i < rowCount(); i++)
    {
        int id = record(i).field("id").value().toInt();
        if(id == teamId) return i;
    }
    return -1;
}
