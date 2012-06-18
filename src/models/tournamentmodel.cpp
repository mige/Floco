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
