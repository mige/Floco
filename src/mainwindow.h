#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
    DatabaseManager *databaseManager;
};

#endif // MAINWINDOW_H
