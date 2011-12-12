#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <addplayerdlg.h>
#include <databasemanager.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void showAddPlayerDlg();
    void deletePlayer();

private:
    Ui::MainWindow *ui;
    DatabaseManager *databaseManager;
    QSqlTableModel *playerModel;
    AddPlayerDlg *addPlayerDlg;
};

#endif // MAINWINDOW_H
