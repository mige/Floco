#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include <QSqlRelationalTableModel>

/**
 * @brief The PlayerModel class provides the players model from the database.
 */
class PlayerModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit PlayerModel(QObject *parent = 0);

signals:

public slots:

};

#endif // PLAYERMODEL_H
