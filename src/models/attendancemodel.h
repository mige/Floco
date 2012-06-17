#ifndef ATTENDANCEMODEL_H
#define ATTENDANCEMODEL_H

#include <QAbstractTableModel>
#include <QSqlTableModel>
#include <models/playermodel.h>
#include <models/trainingmodel.h>

class AttendanceModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit AttendanceModel(QSqlRecord trainingRecord, QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    ~AttendanceModel();

signals:
    
public slots:
    void saveData();

private:
    int             m_idxTeam;
    int             m_idxTraining;

    PlayerModel     *playersModel;
    TrainingModel   *trainingsModel;
    QSqlTableModel  *model;

    QList<bool>     m_Inserted;
    QList<bool>     m_data;
    QList<int>      m_id;
};

#endif // ATTENDANCEMODEL_H
