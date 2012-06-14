#include "teamstab.h"
#include "ui_teamstab.h"

#include <QList>
#include <QDebug>
#include <QMessageBox>
#include <QSqlField>
#include <QSqlRecord>

/**
 * @brief Creates a tab widget for management teams.
 * @param parent The parent widget.
 */
TeamsTab::TeamsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeamsTab)
{
    ui->setupUi(this);

    QList<int> sizes = ui->splitter->sizes();
    sizes[0] = 250;
    sizes[1] = 2500; // hack for full stretch
    ui->splitter->setSizes(sizes);

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(showAddTeamDlg()));
    connect(ui->btnEdit, SIGNAL(clicked()), this, SLOT(showEditTeamDlg()));
    connect(ui->btnDelete, SIGNAL(clicked()), this, SLOT(deleteTeam()));
    connect(ui->listView, SIGNAL(activated(QModelIndex)), this, SLOT(changePlayerFilter(QModelIndex)));
    connect(ui->listView, SIGNAL(entered(QModelIndex)), this, SLOT(changePlayerFilter(QModelIndex)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTeamFilter(int)));

    teamModel = new QSqlTableModel(this);
    teamModel->setTable("team");
    teamModel->select();

    ui->listView->setModel(teamModel);
    ui->listView->setModelColumn(1);

    categoryModel = new CategoryModel(this);
    ui->comboBox->insertItems(1, categoryModel->categoryList());

    playerModel = new PlayerModel(this);
    playerModel->setFilter("team_id=0");
    ui->treeView->setModel(playerModel);
    ui->treeView->hideColumn(0);
    ui->treeView->hideColumn(3);
    ui->treeView->hideColumn(4);
    ui->treeView->hideColumn(5);
    ui->treeView->hideColumn(6);
    ui->treeView->hideColumn(8);
    ui->treeView->hideColumn(10);
}

/**
 * @brief Displays the dialog for add team.
 */
void TeamsTab::showAddTeamDlg()
{
    addTeamDlg = new AddTeamDlg(teamModel);
    addTeamDlg->exec();
    delete addTeamDlg;
    playerModel->select();
}

/**
 * @brief Displays the dialog for editing selected team.
 */
void TeamsTab::showEditTeamDlg()
{
    int teamRow = currentTeamRow();
    if(teamRow == -1) return;

    addTeamDlg = new AddTeamDlg(teamModel, teamRow);
    addTeamDlg->exec();
    delete addTeamDlg;
    playerModel->select();
}

/**
 * @brief Delete the selected teams.
 */
void TeamsTab::deleteTeam()
{
    int teamRow = currentTeamRow();
    if(teamRow == -1) return;

    if(QMessageBox::question(this, tr("Delete team"), tr("Really delete team?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) return;

    // remove id team from players
    QSqlRecord record;
    QSqlField teamId("team_id", QVariant::Int);
    teamId.clear();
    record.append(teamId);

    for(int i = 0; i < playerModel->rowCount(); i++)
        playerModel->setRecord(i, record);
    playerModel->submitAll();

    playerModel->setFilter("team_id=0");

    // delete team

    teamModel->removeRow(teamRow);
    teamModel->submitAll();
}

/**
 * @brief Change players filter by team ID.
 * @param index Index of selected team.
 */
void TeamsTab::changePlayerFilter(QModelIndex index)
{
    int idx = teamModel->record(index.row()).field("id").value().toInt();
    playerModel->setFilter("team_id="+QString::number(idx));
}

/**
 * @brief Change team filter by category ID.
 * @param index Index of selected category.
 */
void TeamsTab::changeTeamFilter(int index)
{
    if(index == 0)
        teamModel->setFilter(QString());
    else
    {
        int idx = categoryModel->record(index-1).field("id").value().toInt();
        teamModel->setFilter("team_category_id = "+QString::number(idx));
    }
    playerModel->setFilter("team_id=0");
}

int TeamsTab::currentTeamRow()
{
    QItemSelectionModel *selmodel = ui->listView->selectionModel();
    QModelIndexList list = selmodel->selectedRows();
    if(list.size() != 1) return -1;
    return list.at(0).row();
}

/**
 * @brief destruct the widget.
 */
TeamsTab::~TeamsTab()
{
    delete categoryModel;
    delete teamModel;
    delete ui;
}
