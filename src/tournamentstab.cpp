#include "tournamentstab.h"
#include "ui_tournamentstab.h"

#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlField>

TournamentsTab::TournamentsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TournamentsTab)
{
    ui->setupUi(this);

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(showAddTournamentDlg()));
    connect(ui->btnEdit, SIGNAL(clicked()), this, SLOT(showEditTournamentDlg()));
    connect(ui->btnDelete, SIGNAL(clicked()), this, SLOT(deleteTournament()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTeamFilter(int)));
    connect(ui->listView, SIGNAL(activated(QModelIndex)), this, SLOT(changeTournamentFilter(QModelIndex)));
    connect(ui->listView, SIGNAL(entered(QModelIndex)), this, SLOT(changeTournamentFilter(QModelIndex)));

    teamModel = new TeamModel;
    categoryModel = new CategoryModel(this);
    model = new TournamentModel;
    model->setFilter("team_id=0");

    ui->listView->setModel(teamModel);
    ui->listView->setModelColumn(1);

    ui->treeView->setModel(model);
    ui->treeView->hideColumn(0);
    ui->treeView->hideColumn(4);
    ui->treeView->sortByColumn(1, Qt::AscendingOrder);
    ui->treeView->header()->resizeSection(1, 120);
    ui->treeView->header()->resizeSection(2, 220);

    ui->comboBox->insertItems(1, categoryModel->categoryList());
}

/**
 * @brief Show the dialog for adding training.
 */
void TournamentsTab::showAddTournamentDlg()
{
    addTournamentDlg = new AddTournamentDlg(model);
    addTournamentDlg->exec();
    delete addTournamentDlg;
}

/**
 * @brief Show the edit dialog for the first selected tournament.
 */
void TournamentsTab::showEditTournamentDlg()
{
    QItemSelectionModel *selmodel = ui->treeView->selectionModel();
    QModelIndexList list = selmodel->selectedRows();

    if(list.size() > 0)
    {
        addTournamentDlg = new AddTournamentDlg(model, list.at(0).row());
        addTournamentDlg->exec();
        delete addTournamentDlg;
    }
}

/**
 * @brief Deletes the selected tournaments.
 */
void TournamentsTab::deleteTournament()
{
    QItemSelectionModel *selmodel = ui->treeView->selectionModel();
    QModelIndexList list = selmodel->selectedRows();

    if(list.size() > 0)
        if(QMessageBox::question(this, tr("Delete tournaments"), tr("Really delete tournaments?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) return;

    for(int i = 0; i < list.size(); i++)
        model->removeRow(list.at(i).row());

    model->submitAll();
}

/**
 * @brief Change team filter by category ID.
 * @param index Index of selected category.
 */
void TournamentsTab::changeTeamFilter(int index)
{
    if(index == 0)
        teamModel->setFilter(QString());
    else
    {
        int idx = categoryModel->record(index-1).field("id").value().toInt();
        teamModel->setFilter("team_category_id = "+QString::number(idx));
    }
    model->setFilter("team_id=0");
}

/**
 * @brief Change tournaments filter by team ID.
 * @param index Index of selected team.
 */
void TournamentsTab::changeTournamentFilter(QModelIndex index)
{
    int idx = teamModel->record(index.row()).field("id").value().toInt();
    model->setFilter("team_id="+QString::number(idx));
}

/**
 * @brief Destruct the widget.
 */
TournamentsTab::~TournamentsTab()
{
    delete teamModel;
    delete categoryModel;
    delete model;
    delete ui;
}
