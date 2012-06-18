#ifndef TEAMMODEL_H
#define TEAMMODEL_H

#include <QSqlRelationalTableModel>

/**
 * @brief The TeamModel class provides the team model from the database.
 */
class TeamModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit TeamModel(QObject *parent = 0);
    int getPosition(int teamId);

signals:

public slots:

};

#endif // TEAMMODEL_H
