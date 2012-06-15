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
    explicit AddTrainingDlg(TrainingModel *model, int trainingRow = -1, QWidget *parent = 0);
    ~AddTrainingDlg();

public slots:
    void addTraining();
    void addTrainingAndClose();
    void saveTraining();

private:
    QSqlRecord          createRecord(QDateTime datetime, int teamID);
    QList<QSqlRecord>   prepareRecords();
    bool                insertTrainings();
    bool                checkForm(QString title);

    Ui::AddTrainingDlg  *ui;
    TeamModel           *teamModel;
    TrainingModel       *trainingModel;
    QDate               startSeason;
    QDate               endSeason;
    int                 m_row;
};

#endif // ADDTRAININGDLG_H
