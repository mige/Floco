#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QDebug>
#include <QMessageBox>

/**
 * @brief Creates a main window.
 * @param parent Parent widget.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QString dbFilePath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);

    databaseManager = DatabaseManager::getInstance();
    if(!databaseManager->open(dbFilePath, "floco.db"))
        QMessageBox::critical(this, tr("Floco"), tr("Cannot open database file!"));

    ui->setupUi(this); // UI setup must be after database connection otherwise
                       // they will not work models correctly in other class

    connect(ui->actionEdit_categories, SIGNAL(triggered()), this, SLOT(showEditCategories()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
}

/**
 * @brief Show the edit categories dialog.
 */
void MainWindow::showEditCategories()
{
    editCategoriesDlg = new EditCategoriesDlg();
    editCategoriesDlg->exec();
    delete editCategoriesDlg;
}

/**
 * @brief Show the about dialog.
 */
void MainWindow::showAbout()
{
    QMessageBox::about(this, tr("About Floco"), tr("Created by Aleš Nejdr"));
}

/**
 * @brief Close the database connection and destruct the window.
 */
MainWindow::~MainWindow()
{
    databaseManager->close();
    delete databaseManager;
    delete ui;
}
