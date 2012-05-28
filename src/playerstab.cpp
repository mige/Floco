#include "playerstab.h"
#include "ui_playerstab.h"

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
    connect(ui->treePlayers, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(showDetails(QModelIndex)));
    connect(ui->btnBackToPlayersList, SIGNAL(clicked()), this, SLOT(showPlayersList()));
    connect(ui->editFiltr, SIGNAL(textChanged(QString)), this, SLOT(changeFilter(QString)));

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
    QModelIndexList list = selmodel->selectedIndexes();

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
    QModelIndexList list = selmodel->selectedIndexes();

    if(list.size() > 0)
        if(QMessageBox::question(this, tr("Delete players"), tr("Really delete players?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) return;

    for(int i = 0; i < list.size(); i++)
        model->removeRow(list.at(i).row());
    model->submitAll();
}

/**
 * @brief Displays detailed info player by index.
 * @param index Index player in model.
 */
void PlayersTab::showDetails(QModelIndex index)
{
    QSqlRecord record = model->record(index.row());

    ui->txtPlayerName->setText(record.field("firstname").value().toString()+" "+record.field("surname").value().toString());
    ui->txtNumber->setText(tr("Number: <b>")+QString::number(record.field("number").value().toInt()));
    ui->txtPost->setText(tr("Post: <b>")+record.field("post").value().toString());
    ui->txtBirth->setText(tr("Day of birth: <b>")+record.field("birth").value().toDate().toString("d.M.yyyy"));
    ui->txtAddress->setText(tr("Address: <b>")+record.field("address").value().toString());
    ui->txtPhone->setText(tr("Phone: <b>")+record.field("phone").value().toString());
    ui->txtMail->setText(tr("E-mail: <b>")+record.field("email").value().toString());

    QByteArray photoData = record.field("photo").value().toByteArray();
    QPixmap photo;

    if(photoData.isNull()) photo.load(":/icons/icons/player-128.png");
    else photo.loadFromData(record.field("photo").value().toByteArray());

    ui->photo->setPixmap(photo);

    ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief Displays players list.
 */
void PlayersTab::showPlayersList()
{
    ui->stackedWidget->setCurrentIndex(0);
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
