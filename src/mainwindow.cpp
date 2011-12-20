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

    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));

    playerModel = new QSqlTableModel(this); // TODO: QSqlRelationalTableModel
    playerModel->setTable("player");
    playerModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    playerModel->select();
    ui->tabPlayers->setModel(playerModel);
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, tr("About Floco"), tr("Created by Aleš Nejdr"));
}

MainWindow::~MainWindow()
{
    qDebug() << databaseManager->lastError();
    databaseManager->close();
    delete ui;
}
