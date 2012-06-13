#ifndef ADDTRAININGDLG_H
#define ADDTRAININGDLG_H

#include <QDateTime>
#include <QDialog>
#include <QSqlRecord>
#include <models/teammodel.h>
#include <models/trainingmodel.h>

namespace Ui {
    class AddTrainingDlg;
}

/**
 * @brief The AddTrainingDlg class provides the window for adding or editing trainings.
 */
class AddTrainingDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddTrainingDlg(TrainingModel *model, QWidget *parent = 0);
    ~AddTrainingDlg();

public slots:
    void addTraining();
    void addTrainingAndClose();

private:
    QSqlRecord          createRecord(QDateTime datetime, int teamID);
    QList<QSqlRecord>   prepareRecords();
    bool                insertTrainings();

    Ui::AddTrainingDlg  *ui;
    TeamModel           *teamModel;
    TrainingModel       *trainingModel;
    QDate               startSeason;
    QDate               endSeason;
};

#endif // ADDTRAININGDLG_H
