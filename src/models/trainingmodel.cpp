#include "trainingmodel.h"

#include <QCheckBox>
#include <QDateTime>

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

    return value;
}
