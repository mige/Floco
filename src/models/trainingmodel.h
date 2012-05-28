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

signals:

public slots:

};

#endif // TRAININGMODEL_H
