#ifndef ADDTEAMDLG_H
#define ADDTEAMDLG_H

#include <QDialog>

namespace Ui {
    class AddTeamDlg;
}

class AddTeamDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddTeamDlg(QWidget *parent = 0);
    ~AddTeamDlg();

private:
    Ui::AddTeamDlg *ui;
};

#endif // ADDTEAMDLG_H
