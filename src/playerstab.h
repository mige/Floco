#ifndef PLAYERSTAB_H
#define PLAYERSTAB_H

#include <QWidget>
#include <addplayerdlg.h>
#include <models/playermodel.h>

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
    void changeFilter(const QString& text);

private:
    Ui::PlayersTab  *ui;
    AddPlayerDlg    *addPlayerDlg;
    PlayerModel     *model;
};

#endif // PLAYERSTAB_H
