#ifndef ADDTOURNAMENTDLG_H
#define ADDTOURNAMENTDLG_H

#include <QDialog>
#include <models/tournamentmodel.h>
#include <models/teammodel.h>

namespace Ui {
class AddTournamentDlg;
}

class AddTournamentDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddTournamentDlg(TournamentModel *model, int tournamentRow = -1, QWidget *parent = 0);
    ~AddTournamentDlg();

public slots:
    void addTournament();
    void addTournamentAndClose();
    void saveEditedTournament();
    
private:
    bool        insertTournament();
    QSqlRecord  createRecord();
    bool        checkForm(QString title);


    Ui::AddTournamentDlg *ui;
    TournamentModel      *model;
    TeamModel            *teamModel;
    int                  tournamentRow;
};

#endif // ADDTOURNAMENTDLG_H
