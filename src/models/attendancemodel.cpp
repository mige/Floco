#include "attendancemodel.h"

#include <QSqlField>
#include <QSqlRecord>

AttendanceModel::AttendanceModel(QSqlRecord trainingRecord, QObject *parent) :
    QAbstractTableModel(parent)
{
    playersModel = new PlayerModel();
    trainingsModel = new TrainingModel();

    m_idxTeam = trainingRecord.field("team_id").value().toInt();
    m_idxTraining = trainingRecord.field("id").value().toInt();

    playersModel->setFilter("team_id = "+QString::number(m_idxTeam));
    playersModel->sort(2, Qt::AscendingOrder);

    model = new QSqlTableModel();
    model->setTable("attendance");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->sort(1, Qt::DescendingOrder);

    for(int i = 0; i < playersModel->rowCount(); i++)
    {
        int id = playersModel->record(i).field("id").value().toInt();
        model->setFilter("training_id = "+QString::number(m_idxTraining)+" AND player_id = "+QString::number(id));
                if(model->rowCount() != 0)
        {
            m_Inserted.append(true);
            m_data.append(model->record(0).field("participated").value().toBool());
        }
        else
        {
            m_Inserted.append(false);
            m_data.append(false);
        }
        m_id.append(id);
    }

    model->setFilter("training_id = "+m_idxTraining);
}

/**
 * @brief Return row count
 * @param parent Not use
 * @return Row count
 */
int AttendanceModel::rowCount(const QModelIndex &parent) const
{
    return playersModel->rowCount();
}

/**
 * @brief Columnt count
 * @param parent Not use
 * @return Allways return 2
 */
int AttendanceModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

/**
 * @brief AttendanceModel::data
 * @param index
 * @param role
 * @return Data
 */
QVariant AttendanceModel::data(const QModelIndex &index, int role) const
{
    if(index.column() == 0 && role == Qt::DisplayRole)
    {
        QSqlRecord record = playersModel->record(index.row());
        QString firstname = record.field("firstname").value().toString();
        QString surname = record.field("surname").value().toString();
        return QVariant(surname +" " + firstname);
    }
    else if(index.column() == 1)
    {
        if(role == Qt::DisplayRole)
        {
            return m_data.at(index.row()) ? QVariant(tr("Yes")) : QVariant(tr("No"));
        }
        if(role == Qt::CheckStateRole)
        {
            return m_data.at(index.row()) ? Qt::Checked : Qt::Unchecked;
        }
    }
    return QVariant();
}

/**
 * @brief Set chcecked state to canceled
 * @param index Model index
 * @param value Value
 * @param role Role
 * @return true
 */
bool AttendanceModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::CheckStateRole && index.column() == 1)
    {
        m_data.replace(index.row(), value.toBool());
    }
    emit dataChanged(index, index);
    return true;
}

/**
 * @brief Flags for model item from model index.
 * @param index Model index
 * @return Item flags
 */
Qt::ItemFlags AttendanceModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);

    if(index.column() == 1)
    {
        flags |= Qt::ItemIsEditable;
        flags |= Qt::ItemIsUserCheckable;
    }

    return flags;
}

/**
 * @brief AttendanceModel::headerData
 * @param section
 * @param orientation
 * @param role
 * @return
 */
QVariant AttendanceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if(section == 0) return QVariant(tr("Player"));
        if(section == 1) return QVariant(tr("Was present?"));
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

/**
 * @brief Save data to table.
 */
void AttendanceModel::saveData()
{
    for(int i = 0; i < m_data.size(); i++)
    {
        QSqlRecord record;
        QSqlField idPlayer("player_id", QVariant::Int);
        QSqlField idTraining("training_id", QVariant::Int);
        QSqlField participated("participated", QVariant::Bool);

        idPlayer.setValue(m_id.at(i));
        idTraining.setValue(m_idxTraining);
        participated.setValue(m_data.at(i));

        record.append(idPlayer);
        record.append(idTraining);
        record.append(participated);
        if(m_Inserted.at(i))
        {
            model->setFilter("training_id = "+QString::number(m_idxTraining)+" AND player_id = "+QString::number(m_id.at(i)));
            model->select();
            model->setRecord(0, record);
        }
        else
        {
            model->insertRecord(-1, record);
            m_Inserted.replace(i, true);
        }
        model->submitAll();
    }

    model->setFilter("training_id = "+m_idxTraining);
    model->select();
}

AttendanceModel::~AttendanceModel()
{
    delete model;
    delete trainingsModel;
    delete playersModel;
}
