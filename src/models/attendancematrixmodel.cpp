#include "attendancematrixmodel.h"

#include <QDebug>
#include <QDateTime>
#include <QSqlRecord>
#include <QSqlField>

AttendanceMatrixModel::AttendanceMatrixModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    playerModel = new PlayerModel;
    trainingModel = new TrainingModel;
    model = new QSqlTableModel;
    model->setTable("attendance");
    model->select();
}

QVariant AttendanceMatrixModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Vertical)
        {
            QSqlRecord record = playerModel->record(section);
            QString firstname = record.field("firstname").value().toString();
            QString surname = record.field("surname").value().toString();
            return QVariant(surname +" "+ firstname);
        }
        else
        {
            QDateTime datetime = trainingModel->record(section).field("datetime").value().toDateTime();
            return QVariant(datetime.toString(tr("dd.MM.yyyy h:mm")));
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

int AttendanceMatrixModel::rowCount(const QModelIndex &parent) const
{
    return playerModel->rowCount();
}

int AttendanceMatrixModel::columnCount(const QModelIndex &parent) const
{
    return trainingModel->rowCount();
}

QVariant AttendanceMatrixModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        int pId = playerModel->record(index.row()).field("id").value().toInt();
        int tId = trainingModel->record(index.column()).field("id").value().toInt();

        model->setFilter("training_id = "+QString::number(tId)+" AND player_id = "+QString::number(pId));

        bool is = model->record(0).field("participated").value().toBool();
        return is ? QVariant(tr("Yes")) : QVariant(tr("No"));
    }

    return QVariant();
}

void AttendanceMatrixModel::setTeam(int idTeam)
{
    playerModel->setFilter("team_id = "+QString::number(idTeam));
    playerModel->sort(2, Qt::AscendingOrder);
    playerModel->select();

    trainingModel->setFilter("team_id = "+QString::number(idTeam));
    trainingModel->sort(1, Qt::AscendingOrder);
    trainingModel->select();

    emit layoutChanged();
}

AttendanceMatrixModel::~AttendanceMatrixModel()
{
    delete playerModel;
    delete trainingModel;
}
