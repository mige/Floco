#include "addteamdlg.h"
#include "ui_addteamdlg.h"

AddTeamDlg::AddTeamDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTeamDlg)
{
    ui->setupUi(this);

    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
}

AddTeamDlg::~AddTeamDlg()
{
    delete ui;
}
