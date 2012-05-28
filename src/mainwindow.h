#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <databasemanager.h>
#include <editcategoriesdlg.h>

namespace Ui {
    class MainWindow;
}

/**
 * @brief The MainWindow class provides the main window. Yeah!
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void showAbout();
    void showEditCategories();

private:
    Ui::MainWindow      *ui;
    DatabaseManager     *databaseManager;
    EditCategoriesDlg   *editCategoriesDlg;
};

#endif // MAINWINDOW_H
