#ifndef TRAININGSTAB_H
#define TRAININGSTAB_H

#include <QWidget>
#include <addtrainingdlg.h>
#include <models/categorymodel.h>
#include <models/teammodel.h>
#include <models/trainingmodel.h>
#include <recordattendancedlg.h>

namespace Ui {
    class TrainingsTab;
}

/**
 * @brief The TrainingsTab class provides tab widget for management training.
 */
class TrainingsTab : public QWidget
{
    Q_OBJECT

public:
    explicit TrainingsTab(QWidget *parent = 0);
    ~TrainingsTab();

public slots:
    void showAddTrainingDlg();
    void showEditTrainingDlg();
    void showRecordAttendanceDlg();
    void deleteTraining();
    void changeTeamFilter(int index);
    void changeTrainingFilter(QModelIndex index);

private:
    Ui::TrainingsTab    *ui;
    AddTrainingDlg      *addTrainingDlg;
    RecordAttendanceDlg *recordAttendanceDlg;
    TeamModel           *teamModel;
    TrainingModel       *trainingModel;    
    CategoryModel       *categoryModel;
};

#endif // TRAININGSTAB_H
