#include "attendancetab.h"
#include "ui_attendancetab.h"

/**
 * @brief Creates a tab widget for viewing attendance.
 * @param parent Parent widget.
 */
AttendanceTab::AttendanceTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AttendanceTab)
{
    ui->setupUi(this);
}

/**
 * @brief Destructs the widget.
 */
AttendanceTab::~AttendanceTab()
{
    delete ui;
}
