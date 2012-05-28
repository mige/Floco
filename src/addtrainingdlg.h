#ifndef ADDTRAININGDLG_H
#define ADDTRAININGDLG_H

#include <QDialog>
#include <models/teammodel.h>

namespace Ui {
    class AddTrainingDlg;
}

/**
 * @brief The AddTrainingDlg class provides the window for adding or editing trainings.
 */
class AddTrainingDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddTrainingDlg(QWidget *parent = 0);
    ~AddTrainingDlg();

private:
    Ui::AddTrainingDlg  *ui;
    TeamModel           *teamModel;
};

#endif // ADDTRAININGDLG_H
