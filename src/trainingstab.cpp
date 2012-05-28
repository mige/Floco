#include "trainingstab.h"
#include "ui_trainingstab.h"

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

    teamModel = new TeamModel;
    trainingModel = new TrainingModel;

    ui->listView->setModel(teamModel);
    ui->listView->setModelColumn(1);

    ui->treeView->setModel(trainingModel);
    ui->treeView->hideColumn(0);
    ui->treeView->hideColumn(5);
}

/**
 * @brief Show the dialog for adding training.
 */
void TrainingsTab::showAddTrainingDlg()
{
    addTrainingDlg = new AddTrainingDlg;
    addTrainingDlg->exec();
    delete addTrainingDlg;
}

/**
 * @brief Destruct the widget.
 */
TrainingsTab::~TrainingsTab()
{
    delete ui;
}
