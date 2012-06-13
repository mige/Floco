#ifndef TRAININGSTAB_H
#define TRAININGSTAB_H

#include <QWidget>
#include <addtrainingdlg.h>
#include <models/teammodel.h>
#include <models/trainingmodel.h>

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

private:
    Ui::TrainingsTab    *ui;
    AddTrainingDlg      *addTrainingDlg;
    TeamModel           *teamModel;
    TrainingModel       *trainingModel;
};

#endif // TRAININGSTAB_H
