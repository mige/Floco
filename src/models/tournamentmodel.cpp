#include "tournamentmodel.h"

TournamentModel::TournamentModel(QObject *parent) :
    QSqlTableModel(parent)
{
    setTable("tournament");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();

    setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    setHeaderData(2, Qt::Horizontal, QObject::tr("Place"));
    setHeaderData(3, Qt::Horizontal, QObject::tr("In season"));
}

/**
 * @brief Return data
 * @param index Model index
 * @param role Role
 * @return Data
 */
QVariant TournamentModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) return QVariant();

    QVariant value = QSqlTableModel::data(index, role);

    if(role == Qt::DisplayRole)
    {
        if(index.column() == 3)
        {
            bool isChecked = value.toBool();
            return isChecked ? QVariant(tr("In season")) : QVariant("Off season");
        }
    }

    return value;
}
