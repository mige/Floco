#ifndef TOURNAMENTSTAB_H
#define TOURNAMENTSTAB_H

#include <QWidget>
#include <addtournamentdlg.h>
#include <models/teammodel.h>
#include <models/categorymodel.h>
#include <models/tournamentmodel.h>

namespace Ui {
class TournamentsTab;
}

class TournamentsTab : public QWidget
{
    Q_OBJECT
    
public:
    explicit TournamentsTab(QWidget *parent = 0);
    ~TournamentsTab();

public slots:
    void changeTeamFilter(int index);
    void showAddTournamentDlg();
    void showEditTournamentDlg();
    void deleteTournament();
    void changeTournamentFilter(QModelIndex index);
    
private:
    Ui::TournamentsTab *ui;

    TeamModel           *teamModel;
    CategoryModel       *categoryModel;
    TournamentModel     *model;

    AddTournamentDlg    *addTournamentDlg;
};

#endif // TOURNAMENTSTAB_H
