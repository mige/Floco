#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include <QSqlRelationalTableModel>

class PlayerModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit PlayerModel(QObject *parent = 0);

signals:

public slots:

};

#endif // PLAYERMODEL_H
