#include "trainingstab.h"
#include "ui_trainingstab.h"

#include <QMessageBox>
#include <QSqlField>

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
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTeamFilter(int)));
    connect(ui->listView, SIGNAL(activated(QModelIndex)), this, SLOT(changeTrainingFilter(QModelIndex)));
    connect(ui->listView, SIGNAL(entered(QModelIndex)), this, SLOT(changeTrainingFilter(QModelIndex)));
    connect(ui->btnRecordAttendance, SIGNAL(clicked()), this, SLOT(showRecordAttendanceDlg()));

    teamModel = new TeamModel;
    trainingModel = new TrainingModel;

    ui->listView->setModel(teamModel);
    ui->listView->setModelColumn(1);

    ui->treeView->setModel(trainingModel);
    ui->treeView->hideColumn(0);
    ui->treeView->hideColumn(4);

    categoryModel = new CategoryModel(this);
    ui->comboBox->insertItems(1, categoryModel->categoryList());
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
 * @brief Change trainings filter by team ID.
 * @param index Index of selected team.
 */
void TrainingsTab::changeTrainingFilter(QModelIndex index)
{
    int idx = teamModel->record(index.row()).field("id").value().toInt();
    trainingModel->setFilter("team_id="+QString::number(idx));
}

/**
 * @brief Change team filter by category ID.
 * @param index Index of selected category.
 */
void TrainingsTab::changeTeamFilter(int index)
{
    if(index == 0)
        teamModel->setFilter(QString());
    else
    {
        int idx = categoryModel->record(index-1).field("id").value().toInt();
        teamModel->setFilter("team_category_id = "+QString::number(idx));
    }
    trainingModel->setFilter("team_id=0");
}

/**
 * @brief Displays the dialog for record attendance of selected training.
 */
void TrainingsTab::showRecordAttendanceDlg()
{
    QItemSelectionModel *selmodel = ui->treeView->selectionModel();
    QModelIndexList list = selmodel->selectedRows();

    if(list.size() == 0) return;

    recordAttendanceDlg = new RecordAttendanceDlg(trainingModel->record(list.at(0).row()));
    recordAttendanceDlg->exec();
    delete recordAttendanceDlg;
}

/**
 * @brief Destruct the widget.
 */
TrainingsTab::~TrainingsTab()
{
    delete ui;
}
