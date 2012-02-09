#include "attendancetab.h"
#include "ui_attendancetab.h"

AttendanceTab::AttendanceTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AttendanceTab)
{
    ui->setupUi(this);
}

AttendanceTab::~AttendanceTab()
{
    delete ui;
}
