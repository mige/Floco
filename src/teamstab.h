#ifndef TEAMSTAB_H
#define TEAMSTAB_H

#include <QWidget>
#include <addteamdlg.h>

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

private:
    Ui::TeamsTab *ui;
    AddTeamDlg *addTeamDlg;
};

#endif // TEAMSTAB_H
