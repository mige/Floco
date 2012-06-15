#ifndef TRAININGMODEL_H
#define TRAININGMODEL_H

#include <QSqlTableModel>

/**
 * @brief The TrainingModel class provides the training model from the database.
 */
class TrainingModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit TrainingModel(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

signals:

public slots:

};

#endif // TRAININGMODEL_H
