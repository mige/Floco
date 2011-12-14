#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString dbFilePath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);

    databaseManager = DatabaseManager::getInstance();
    if(!databaseManager->open(dbFilePath, "floco.db"))
        QMessageBox::critical(this, tr("Floco"), tr("Cannot open database file!"));

    playerModel = new QSqlTableModel(this); // TODO: QSqlRelationalTableModel
    playerModel->setTable("player");
    playerModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    playerModel->select();

    playerModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    playerModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Firstname"));
    playerModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Surname"));
    playerModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Date of birth"));
    playerModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Address"));
    playerModel->setHeaderData(5, Qt::Horizontal, QObject::tr("E-mail"));
    playerModel->setHeaderData(6, Qt::Horizontal, QObject::tr("Phone"));

    ui->treePlayers->setModel(playerModel);
    ui->treePlayers->hideColumn(0);
    ui->treePlayers->hideColumn(7);
    ui->treePlayers->hideColumn(8);
    ui->treePlayers->hideColumn(9);
    ui->treePlayers->hideColumn(10);
    ui->treePlayers->header()->moveSection(1, 2);
    ui->treePlayers->sortByColumn(2, Qt::AscendingOrder);

    connect(ui->actionAddPlayer, SIGNAL(triggered()), this, SLOT(showAddPlayerDlg()));
    connect(ui->actionEditPlayer,SIGNAL(triggered()), this, SLOT(editPlayer()));
    connect(ui->actionDeletePlayer, SIGNAL(triggered()), this, SLOT(deletePlayer()));
}

void MainWindow::showAddPlayerDlg()
{
    addPlayerDlg = new AddPlayerDlg(playerModel);
    addPlayerDlg->exec();
    delete addPlayerDlg;
}

void MainWindow::editPlayer()
{
    QItemSelectionModel *selmodel = ui->treePlayers->selectionModel();
    QModelIndexList list = selmodel->selectedIndexes();

    if(list.size() > 0)
    {
        addPlayerDlg = new AddPlayerDlg(playerModel, list.at(0).row());
        addPlayerDlg->exec();
        delete addPlayerDlg;
    }
}

void MainWindow::deletePlayer()
{
    QItemSelectionModel *selmodel = ui->treePlayers->selectionModel();
    QModelIndexList list = selmodel->selectedIndexes();

    if(list.size() > 0)
        if(QMessageBox::question(this, tr("Delete players"), tr("Really delete players?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) return;

    for(int i = 0; i < list.size(); i++)
        playerModel->removeRow(list.at(i).row());
    playerModel->submitAll();
}

MainWindow::~MainWindow()
{
    qDebug() << databaseManager->lastError();
    databaseManager->close();
    delete playerModel;
    delete ui;
}
