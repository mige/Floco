#include "trainingstab.h"
#include "ui_trainingstab.h"

#include <QMessageBox>

/**
 * @brief Creates a tab widget for management training.
 * @param parent Parent widget.
 */
TrainingsTab::TrainingsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrainingsTab)
{
    ui->setupUi(this);

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(showAddTrainingDlg()));
    connect(ui->btnEdit, SIGNAL(clicked()), this, SLOT(showEditTrainingDlg()));
    connect(ui->btnDelete, SIGNAL(clicked()), this, SLOT(deleteTraining()));

    teamModel = new TeamModel;
    trainingModel = new TrainingModel;

    ui->listView->setModel(teamModel);
    ui->listView->setModelColumn(1);

    ui->treeView->setModel(trainingModel);
    ui->treeView->hideColumn(0);
    ui->treeView->hideColumn(4);
}

/**
 * @brief Show the dialog for adding training.
 */
void TrainingsTab::showAddTrainingDlg()
{
    addTrainingDlg = new AddTrainingDlg(trainingModel);
    addTrainingDlg->exec();
    delete addTrainingDlg;
}

/**
 * @brief Displays the dialog for editting selected training.
 */
void TrainingsTab::showEditTrainingDlg()
{
    QItemSelectionModel *selmodel = ui->treeView->selectionModel();
    QModelIndexList list = selmodel->selectedIndexes();

    if(list.size() == 0) return;

    addTrainingDlg = new AddTrainingDlg(trainingModel, list.at(0).row());
    addTrainingDlg->exec();
    delete addTrainingDlg;
}

/**
 * @brief Deletes the selected trainings.
 */
void TrainingsTab::deleteTraining()
{
    QItemSelectionModel *selmodel = ui->treeView->selectionModel();
    QModelIndexList list = selmodel->selectedIndexes();

    if(list.size() > 0)
        if(QMessageBox::question(this, tr("Delete trainings"), tr("Really delete trainings?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) return;

    for(int i = 0; i < list.size(); i++)
        trainingModel->removeRow(list.at(i).row());
    trainingModel->submitAll();
}


/**
 * @brief Destruct the widget.
 */
TrainingsTab::~TrainingsTab()
{
    delete ui;
}
