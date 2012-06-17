#include "playerstab.h"
#include "ui_playerstab.h"

#include <playerdetails.h>
#include <QDate>
#include <QMessageBox>
#include <QSqlField>
#include <QSqlRecord>
#include <QDebug>

/**
 * @brief Creates a tab widget for management players.
 * @param parent The parent widget.
 */
PlayersTab::PlayersTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayersTab)
{
    ui->setupUi(this);

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(showAddPlayerDlg()));
    connect(ui->btnEdit, SIGNAL(clicked()), this, SLOT(editPlayer()));
    connect(ui->btnDelete, SIGNAL(clicked()), this, SLOT(deletePlayer()));
    connect(ui->treePlayers, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(showDetailsDialog(QModelIndex)));
    connect(ui->editFiltr, SIGNAL(textChanged(QString)), this, SLOT(changeFilter(QString)));
    connect(ui->btnShowPlayersDetails, SIGNAL(clicked()), this, SLOT(showPlayersDetails()));

    model = new PlayerModel(this);

    ui->treePlayers->setModel(model);
    ui->treePlayers->hideColumn(0);
    ui->treePlayers->hideColumn(7);
    ui->treePlayers->hideColumn(8);
    ui->treePlayers->hideColumn(9);
    ui->treePlayers->hideColumn(10);
    ui->treePlayers->header()->moveSection(1, 2);
    ui->treePlayers->sortByColumn(2, Qt::AscendingOrder);
}

/**
 * @brief Show the dialog for add player.
 */
void PlayersTab::showAddPlayerDlg()
{
    addPlayerDlg = new AddPlayerDlg(model);
    addPlayerDlg->exec();
    delete addPlayerDlg;
}

/**
 * @brief Show the dialog for the first selected player.
 */
void PlayersTab::editPlayer()
{
    QItemSelectionModel *selmodel = ui->treePlayers->selectionModel();
    QModelIndexList list = selmodel->selectedRows();

    if(list.size() > 0)
    {
        addPlayerDlg = new AddPlayerDlg(model, list.at(0).row());
        addPlayerDlg->exec();
        delete addPlayerDlg;
    }
}

/**
 * @brief Deletes the selected players.
 */
void PlayersTab::deletePlayer()
{
    QItemSelectionModel *selmodel = ui->treePlayers->selectionModel();
    QModelIndexList list = selmodel->selectedRows();

    if(list.size() > 0)
        if(QMessageBox::question(this, tr("Delete players"), tr("Really delete players?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) return;

    QSqlTableModel *attendanceModel = new QSqlTableModel();
    attendanceModel->setTable("attendance");

    for(int i = 0; i < list.size(); i++)
    {
        int row = list.at(i).row();
        int id = model->record(row).field("id").value().toInt();

        attendanceModel->setFilter("player_id = "+QString::number(id));
        attendanceModel->select();
        attendanceModel->removeRows(0, attendanceModel->rowCount());
        attendanceModel->submitAll();

        model->removeRow(row);
    }

    delete attendanceModel;
    model->submitAll();
}

/**
 * @brief Displays detailed info player by index on modeless dialog.
 * @param index Index player in model.
 */
void PlayersTab::showDetailsDialog(QModelIndex index)
{
    QSqlRecord record = model->record(index.row());

    PlayerDetails *pd = new PlayerDetails(record, this);
    pd->setAttribute(Qt::WA_DeleteOnClose);
    pd->show();
    pd->raise();
    pd->activateWindow();
}

/**
 * @brief Displays detailed info player on modeless dialog.
 * @sa showDetailsDialog()
 */
void PlayersTab::showPlayersDetails()
{
    QItemSelectionModel *selmodel = ui->treePlayers->selectionModel();
    QModelIndexList list = selmodel->selectedRows();

    for(int i = 0; i < list.size(); i++)
        showDetailsDialog(list.at(i));
}

/**
 * @brief Filter players by firstname and surname.
 * @param text Filter text.
 */
void PlayersTab::changeFilter(const QString &text)
{
    if(text == "" || text == tr("Filter..."))
        model->setFilter(QString());
    else
        model->setFilter("firstname like '%"+text+"%' or surname like '%"+text+"%'");
}

/**
 * @brief Destruct the widget.
 */
PlayersTab::~PlayersTab()
{
    delete model;
    delete ui;
}
