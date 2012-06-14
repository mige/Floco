#ifndef PLAYERSTAB_H
#define PLAYERSTAB_H

#include <QWidget>
#include <addplayerdlg.h>
#include <models/playermodel.h>

namespace Ui {
    class PlayersTab;
}

/**
 * @brief The PlayersTab class provides tab widget for management players.
 */
class PlayersTab : public QWidget
{
    Q_OBJECT

public:
    explicit PlayersTab(QWidget *parent = 0);
    ~PlayersTab();

public slots:
    void showAddPlayerDlg();
    void editPlayer();
    void deletePlayer();
    void showDetailsDialog(QModelIndex index);
    void showPlayersDetails();
    void changeFilter(const QString& text);

private:
    Ui::PlayersTab  *ui;
    AddPlayerDlg    *addPlayerDlg;
    PlayerModel     *model;
};

#endif // PLAYERSTAB_H
