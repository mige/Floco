#include "addteamdlg.h"
#include "ui_addteamdlg.h"

#include <QDebug>
#include <QMessageBox>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlQuery>

/**
 * @brief Creates a dialog for adding or editting team.
 * @param teamModel Team model.
 * @param teamRow Team ID to be edit. If set to -1, dialog provides form for adding team.
 * @param parent Parent widget.
 */
AddTeamDlg::AddTeamDlg(QSqlTableModel *teamModel, int teamRow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTeamDlg)
{
    ui->setupUi(this);

    this->teamModel = teamModel;

    categoryModel = new CategoryModel;
    ui->comboBoxCategory->setModel(categoryModel);
    ui->comboBoxCategory->setModelColumn(1);

    playerRightModel = new PlayerModel;
    playerLeftModel = new PlayerModel;
    fixTeamId(); // fix data after app crash
    playerRightModel->setFilter("team_id is null");

    if(teamRow != -1)
    {
        QSqlRecord record = teamModel->record(teamRow);
        idTeam = record.field("id").value().toInt();
        ui->editName->setText(record.field("name").value().toString());

        playerLeftModel->setFilter("team_id=-1 or team_id="+QString::number(idTeam));
        playerRightModel->setFilter("team_id is null or team_id=0");

        ui->btnAdd->setVisible(false);
        ui->btnAddAndClose->setVisible(false);
        ui->btnSave->setVisible(true);
        setWindowTitle(tr("Edit team"));
        rowTeam = teamRow;

        int categoryId = record.field("team_category_id").value().toInt();

        for(int i = 0; i < categoryModel->rowCount(); i++)
        {
            if(categoryModel->record(i).field("id").value().toInt() == categoryId)
            {
                categoryId = i;
                break;
            }
        }
        ui->comboBoxCategory->setCurrentIndex(categoryId);
    }
    else
    {
        ui->btnSave->setVisible(false);
        idTeam = -1;
    }

    ui->treePlayersInTeam->setModel(playerLeftModel);
    ui->treePlayersInTeam->hideColumn(0);
    ui->treePlayersInTeam->hideColumn(3);
    ui->treePlayersInTeam->hideColumn(4);
    ui->treePlayersInTeam->hideColumn(5);
    ui->treePlayersInTeam->hideColumn(6);
    ui->treePlayersInTeam->hideColumn(7);
    ui->treePlayersInTeam->hideColumn(8);
    ui->treePlayersInTeam->hideColumn(9);
    ui->treePlayersInTeam->hideColumn(10);
    ui->treePlayersInTeam->sortByColumn(2, Qt::AscendingOrder);

    ui->treePlayersWithoutTeam->setModel(playerRightModel);
    ui->treePlayersWithoutTeam->hideColumn(0);
    ui->treePlayersWithoutTeam->hideColumn(3);
    ui->treePlayersWithoutTeam->hideColumn(4);
    ui->treePlayersWithoutTeam->hideColumn(5);
    ui->treePlayersWithoutTeam->hideColumn(6);
    ui->treePlayersWithoutTeam->hideColumn(7);
    ui->treePlayersWithoutTeam->hideColumn(8);
    ui->treePlayersWithoutTeam->hideColumn(9);
    ui->treePlayersWithoutTeam->hideColumn(10);
    ui->treePlayersWithoutTeam->sortByColumn(2, Qt::AscendingOrder);

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(addTeam()));
    connect(ui->btnAddAndClose, SIGNAL(clicked()), this, SLOT(addTeamAndClose()));
    connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(saveTeam()));
    connect(ui->btnLeft, SIGNAL(clicked()), this, SLOT(moveToLeftTree()));
    connect(ui->btnRight, SIGNAL(clicked()), this, SLOT(moveToRightTree()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
}

/**
 * @brief Checks the data from the form and when everything is ok, data is inserted into the model.
 * @sa AddTeamDlg::addTeamAndClose()
 */
void AddTeamDlg::addTeam()
{
    if(insertTeam())
    {
        ui->editName->setText("");
        ui->comboBoxCategory->setCurrentIndex(0);
    }
}

/**
 * @brief Checks the data from the form and when everything is ok, data is inserted into the model and close dialog.
 * @sa AddTeamDlg::addTeam()
 */
void AddTeamDlg::addTeamAndClose()
{
    if(insertTeam()) close();
}

/**
 * @brief Checks the data from the form and when everything is ok, data is edited in the model and close the dialog.
 */
void AddTeamDlg::saveTeam()
{
    if(!checkForm(tr("Edit team"))) return;

    QSqlRecord record = createRecord();
    teamModel->setRecord(rowTeam, record);
    teamModel->submitAll();

    record = getTeamIdRecord(idTeam);

    for(int i = 0; i < playerLeftModel->rowCount(); i++)
        playerLeftModel->setRecord(i, record);
    playerLeftModel->submitAll();

    record = getClearTeamIdRecord();
    for(int i = 0; i < playerRightModel->rowCount(); i++)
        playerRightModel->setRecord(i, record);
    playerRightModel->submitAll();

    close();
}

bool AddTeamDlg::insertTeam()
{
    if(!checkForm(tr("Add team"))) return false;

    QSqlRecord record = createRecord();
    teamModel->insertRecord(-1, record);
    teamModel->submitAll();

    int idx = teamModel->query().lastInsertId().toInt();
    record = getTeamIdRecord(idx);

    for(int i = 0; i < playerLeftModel->rowCount(); i++)
        playerLeftModel->setRecord(i, record);
    playerLeftModel->submitAll();

    return true;
}

QSqlRecord AddTeamDlg::createRecord()
{
    QSqlRecord record;

    QSqlField name("name", QVariant::String);
    QSqlField teamCategoryId("team_category_id", QVariant::Int);

    name.setValue(ui->editName->text().trimmed());

    int idx = ui->comboBoxCategory->currentIndex();
    int categoryIdx = categoryModel->record(idx).field("id").value().toInt();
    teamCategoryId.setValue(categoryIdx);

    record.append(name);
    record.append(teamCategoryId);

    return record;
}

/**
 * @brief Move players from right tree widget to left tree widget.
 */
void AddTeamDlg::moveToLeftTree()
{
    QSqlRecord record = getTeamIdRecord(-1);

    QItemSelectionModel *selmodel = ui->treePlayersWithoutTeam->selectionModel();
    QModelIndexList list = selmodel->selectedIndexes();

    for(int i = 0; i < list.size(); i++)
        playerRightModel->setRecord(list.at(i).row(), record);
    playerRightModel->submitAll();
    playerLeftModel->select();
}

/**
 * @brief Move players from left tree widget to right tree widget.
 */
void AddTeamDlg::moveToRightTree()
{
    QSqlRecord record;
    if(idTeam == -1)
        record = getClearTeamIdRecord();
    else
        record = getTeamIdRecord(0);

    QItemSelectionModel *selmodel = ui->treePlayersInTeam->selectionModel();
    QModelIndexList list = selmodel->selectedIndexes();

    for(int i = 0; i < list.size(); i++)
        playerLeftModel->setRecord(list.at(i).row(), record);
    playerLeftModel->submitAll();
    playerRightModel->select();
}

bool AddTeamDlg::checkForm(QString title)
{
    if(ui->editName->text().trimmed() == "")
    {
        QMessageBox::information(this, title, tr("You must specified team name."));
        return false;
    }
    return true;
}

QSqlRecord AddTeamDlg::getClearTeamIdRecord()
{
    QSqlRecord record;
    QSqlField teamId("team_id", QVariant::Int);
    teamId.clear();
    record.append(teamId);
    return record;
}

QSqlRecord AddTeamDlg::getTeamIdRecord(int teamId)
{
    QSqlRecord record;
    QSqlField teamIdField("team_id", QVariant::Int);
    teamIdField.setValue(teamId);
    record.append(teamIdField);
    return record;
}

void AddTeamDlg::fixTeamId()
{
    playerLeftModel->setFilter("team_id=-1");
    QSqlRecord record = getClearTeamIdRecord();
    for(int i = 0; i < playerLeftModel->rowCount(); i++)
        playerLeftModel->setRecord(i, record);
    playerLeftModel->submitAll();

    if(idTeam != -1)
    {
        playerRightModel->setFilter("team_id=0");
        QSqlRecord record = getTeamIdRecord(idTeam);
        for(int i = 0; i < playerRightModel->rowCount(); i++)
            playerRightModel->setRecord(i, record);
        playerRightModel->submitAll();
    }
}

/**
 * @brief Destructs the dialog and fix team ID for players which is handled, but not the edited.
 */
AddTeamDlg::~AddTeamDlg()
{
    fixTeamId();
    delete playerLeftModel;
    delete playerRightModel;
    delete categoryModel;
    delete ui;
}
