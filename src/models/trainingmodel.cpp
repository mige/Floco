#include "trainingmodel.h"

#include <QCheckBox>
#include <QDateTime>
#include <QSqlField>
#include <QSqlRecord>

/**
 * @brief Creates a training model and set header data.
 * @param parent Parent object.
 */
TrainingModel::TrainingModel(QObject *parent) :
    QSqlTableModel(parent)
{
    setTable("training");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();

    setHeaderData(0, Qt::Horizontal, tr("ID"));
    setHeaderData(1, Qt::Horizontal, tr("Datetime"));
    setHeaderData(2, Qt::Horizontal, tr("Place"));
    setHeaderData(3, Qt::Horizontal, tr("Canceled"));

}

/**
 * @brief Return data
 * @param index Model index
 * @param role Role
 * @return Data
 */
QVariant TrainingModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) return QVariant();

    QVariant value = QSqlTableModel::data(index, role);

    if(role == Qt::DisplayRole)
    {
        if(index.column() == 1)
        {
            QDateTime datetime = value.toDateTime();
            return datetime.toString(tr("dd.MM.yyyy h:mm"));

        }
        else if(index.column() == 3)
        {
            bool isChecked = value.toBool();
            return isChecked ? QVariant(tr("Canceled")) : QVariant();
        }
    }
    else if(role == Qt::CheckStateRole)
    {
        if(index.column() == 3)
        {
            bool isChecked = QSqlTableModel::data(index, Qt::DisplayRole).toBool();
            return isChecked ? Qt::Checked : Qt::Unchecked;
        }
    }

    return value;
}

/**
 * @brief Set chcecked state to canceled
 * @param index Model index
 * @param value Value
 * @param role Role
 * @return true
 */
bool TrainingModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::CheckStateRole && index.column() == 3)
    {
        QSqlRecord record;
        QSqlField canceled("canceled", QVariant::Bool);
        canceled.setValue(value);
        record.append(canceled);
        setRecord(index.row(), record);
        submitAll();
    }
    emit dataChanged(index, index);
    return true;
}

/**
 * @brief Flags for model index.
 * @param index Model index
 * @return Item flags
 */
Qt::ItemFlags TrainingModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);

    if (index.column() == 3)
    {
        flags |= Qt::ItemIsEditable;
        flags |= Qt::ItemIsUserCheckable;
    }

    return flags;
}
