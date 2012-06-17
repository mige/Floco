#ifndef ATTENDANCEMATRIXMODEL_H
#define ATTENDANCEMATRIXMODEL_H

#include <QAbstractTableModel>
#include <QSqlTableModel>
#include <models/playermodel.h>
#include <models/trainingmodel.h>

class AttendanceMatrixModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit AttendanceMatrixModel(QObject *parent = 0);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void setTeam(int idTeam);
    ~AttendanceMatrixModel();

signals:
    
public slots:

private:
    TrainingModel   *trainingModel;
    PlayerModel     *playerModel;
    QSqlTableModel  *model;
};

#endif // ATTENDANCEMATRIXMODEL_H
