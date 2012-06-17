#include "attendancetab.h"
#include "ui_attendancetab.h"

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

    ui->listView->setModel(teamModel);
    ui->listView->setModelColumn(1);
    ui->comboBox->insertItems(1, categoryModel->categoryList());

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTeamFilter(int)));
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
    //rrrtrainingModel->setFilter("team_id=0");
}

/**
 * @brief Destructs the widget.
 */
AttendanceTab::~AttendanceTab()
{
    delete ui;
}
