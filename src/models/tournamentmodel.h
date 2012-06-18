#ifndef TOURNAMENTMODEL_H
#define TOURNAMENTMODEL_H

#include <QSqlTableModel>

class TournamentModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit TournamentModel(QObject *parent = 0);
    QVariant data(const QModelIndex &idx, int role) const;
    
signals:
    
public slots:
    
};

#endif // TOURNAMENTMODEL_H
