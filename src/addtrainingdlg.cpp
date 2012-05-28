#include "addtrainingdlg.h"
#include "ui_addtrainingdlg.h"

AddTrainingDlg::AddTrainingDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTrainingDlg)
{
    ui->setupUi(this);

    teamModel = new TeamModel;
    ui->comboBoxTeam->setModel(teamModel);
    ui->comboBoxTeam->setModelColumn(1);
}

/**
 * @brief Destructs the dialog.
 */
AddTrainingDlg::~AddTrainingDlg()
{
    delete ui;
}
