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
}

MainWindow::~MainWindow()
{
    databaseManager->close();
    delete ui;
}
