#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
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
    void showAbout();

private:
    Ui::MainWindow *ui;
    DatabaseManager *databaseManager;
    QSqlTableModel *playerModel;
};

#endif // MAINWINDOW_H
