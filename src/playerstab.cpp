#include "playerstab.h"
#include "ui_playerstab.h"

#include <QDate>
#include <QMessageBox>
#include <QSqlField>
#include <QSqlRecord>

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
}

void PlayersTab::setModel(QSqlTableModel *playerModel)
{
    model = playerModel;
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Firstname"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Surname"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date of birth"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Address"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("E-mail"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Phone"));

    ui->treePlayers->setModel(model);
    ui->treePlayers->hideColumn(0);
    ui->treePlayers->hideColumn(7);
    ui->treePlayers->hideColumn(8);
    ui->treePlayers->hideColumn(9);
    ui->treePlayers->hideColumn(10);
    ui->treePlayers->header()->moveSection(1, 2);
    ui->treePlayers->sortByColumn(2, Qt::AscendingOrder);
}

void PlayersTab::showAddPlayerDlg()
{
    addPlayerDlg = new AddPlayerDlg(model);
    addPlayerDlg->exec();
    delete addPlayerDlg;
}

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

void PlayersTab::showPlayersList()
{
    ui->stackedWidget->setCurrentIndex(0);
}

PlayersTab::~PlayersTab()
{
    delete model;
    delete ui;
}
