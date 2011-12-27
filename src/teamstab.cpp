#include "teamstab.h"
#include "ui_teamstab.h"

TeamsTab::TeamsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeamsTab)
{
    ui->setupUi(this);

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(showAddTeamDlg()));
}

void TeamsTab::showAddTeamDlg()
{
    addTeamDlg = new AddTeamDlg;
    addTeamDlg->exec();
    delete addTeamDlg;
}

TeamsTab::~TeamsTab()
{
    delete ui;
}
