#include "trainingmodel.h"

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
