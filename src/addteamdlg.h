#ifndef ADDTEAMDLG_H
#define ADDTEAMDLG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <models/playermodel.h>
#include <models/categorymodel.h>

namespace Ui {
    class AddTeamDlg;
}

/**
 * @brief The AddTeamDlg class provides the window for adding or editing teams.
 */
class AddTeamDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddTeamDlg(QSqlTableModel *teamModel, int teamRow = -1, QWidget *parent = 0);
    ~AddTeamDlg();

public slots:
    void moveToLeftTree();
    void moveToRightTree();
    void addTeam();
    void addTeamAndClose();
    void saveTeam();

private:
    void            fixTeamId();
    QSqlRecord      getClearTeamIdRecord();
    QSqlRecord      getTeamIdRecord(int teamId);
    bool            checkForm(QString title);
    bool            insertTeam();
    QSqlRecord      createRecord();

    Ui::AddTeamDlg  *ui;
    QSqlTableModel  *teamModel;
    PlayerModel     *playerRightModel;
    CategoryModel   *categoryModel;
    PlayerModel     *playerLeftModel;
    int             idTeam;
    int             rowTeam;
};

#endif // ADDTEAMDLG_H
