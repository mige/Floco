#ifndef PLAYERSTAB_H
#define PLAYERSTAB_H

#include <QWidget>
#include <QSqlTableModel>
#include <addplayerdlg.h>

namespace Ui {
    class PlayersTab;
}

class PlayersTab : public QWidget
{
    Q_OBJECT

public:
    explicit PlayersTab(QWidget *parent = 0);
    ~PlayersTab();
    void setModel(QSqlTableModel *playerModel);

public slots:
    void showAddPlayerDlg();
    void editPlayer();
    void deletePlayer();
    void showDetails(QModelIndex index);
    void showPlayersList();

private:
    Ui::PlayersTab *ui;
    AddPlayerDlg *addPlayerDlg;
    QSqlTableModel *model;
};

#endif // PLAYERSTAB_H
