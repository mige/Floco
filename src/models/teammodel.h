#ifndef TEAMMODEL_H
#define TEAMMODEL_H

#include <QSqlRelationalTableModel>

class TeamModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit TeamModel(QObject *parent = 0);

signals:

public slots:

};

#endif // TEAMMODEL_H
