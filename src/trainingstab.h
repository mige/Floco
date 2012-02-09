#ifndef TRAININGSTAB_H
#define TRAININGSTAB_H

#include <QWidget>
#include <addtrainingdlg.h>
#include <models/teammodel.h>
#include <models/trainingmodel.h>

namespace Ui {
    class TrainingsTab;
}

class TrainingsTab : public QWidget
{
    Q_OBJECT

public:
    explicit TrainingsTab(QWidget *parent = 0);
    ~TrainingsTab();

public slots:
    void showAddTrainingDlg();

private:
    Ui::TrainingsTab    *ui;
    AddTrainingDlg      *addTrainingDlg;
    TeamModel           *teamModel;
    TrainingModel       *trainingModel;
};

#endif // TRAININGSTAB_H
