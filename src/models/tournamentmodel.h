#ifndef TOURNAMENTMODEL_H
#define TOURNAMENTMODEL_H

#include <QSqlTableModel>

class TournamentModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit TournamentModel(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // TOURNAMENTMODEL_H
