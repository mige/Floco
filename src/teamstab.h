#ifndef TEAMSTAB_H
#define TEAMSTAB_H

#include <QSqlTableModel>
#include <QWidget>
#include <addteamdlg.h>
#include <models/categorymodel.h>
#include <models/playermodel.h>

namespace Ui {
    class TeamsTab;
}

class TeamsTab : public QWidget
{
    Q_OBJECT

public:
    explicit TeamsTab(QWidget *parent = 0);
            ~TeamsTab();

public slots:
    void showAddTeamDlg();
    void showEditTeamDlg();
    void deleteTeam();
    void changePlayerFilter(QModelIndex index);
    void changeTeamFilter(int index);

private:
    Ui::TeamsTab    *ui;
    AddTeamDlg      *addTeamDlg;
    QSqlTableModel  *teamModel;
    CategoryModel   *categoryModel;
    PlayerModel     *playerModel;
    int             currentTeamRow;
};

#endif // TEAMSTAB_H
