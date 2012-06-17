#include "attendancetab.h"
#include "ui_attendancetab.h"

#include <QDebug>
#include <QSqlRecord>
#include <QSqlField>

/**
 * @brief Creates a tab widget for viewing attendance.
 * @param parent Parent widget.
 */
AttendanceTab::AttendanceTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AttendanceTab)
{
    ui->setupUi(this);

    teamModel = new TeamModel;
    categoryModel = new CategoryModel;
    model = new AttendanceMatrixModel();
    model->setTeam(0);

    ui->listView->setModel(teamModel);
    ui->listView->setModelColumn(1);
    ui->comboBox->insertItems(1, categoryModel->categoryList());
    ui->tableView->setModel(model);

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTeamFilter(int)));
    connect(ui->listView, SIGNAL(activated(QModelIndex)), this, SLOT(changeAttendanceFilter(QModelIndex)));
    connect(ui->listView, SIGNAL(entered(QModelIndex)), this, SLOT(changeAttendanceFilter(QModelIndex)));
}

/**
 * @brief Change team filter by category ID.
 * @param index Index of selected category.
 */
void AttendanceTab::changeTeamFilter(int index)
{
    if(index == 0)
        teamModel->setFilter(QString());
    else
    {
        int idx = categoryModel->record(index-1).field("id").value().toInt();
        teamModel->setFilter("team_category_id = "+QString::number(idx));
    }
    model->setTeam(0);
}

/**
 * @brief Change attendance filter by team ID.
 * @param index Index of selected team.
 */
void AttendanceTab::changeAttendanceFilter(QModelIndex index)
{
    int idx = teamModel->record(index.row()).field("id").value().toInt();
    model->setTeam(idx);
}

/**
 * @brief Destructs the widget.
 */
AttendanceTab::~AttendanceTab()
{
    delete teamModel;
    delete categoryModel;
    delete model;
    delete ui;
}
