#ifndef ATTENDANCETAB_H
#define ATTENDANCETAB_H

#include <QWidget>
#include <models/categorymodel.h>
#include <models/teammodel.h>
#include <models/attendancematrixmodel.h>

namespace Ui {
    class AttendanceTab;
}

/**
 * @brief The AttendanceTab class provides tab widget for viewing attendance.
 */
class AttendanceTab : public QWidget
{
    Q_OBJECT

public:
    explicit AttendanceTab(QWidget *parent = 0);
    ~AttendanceTab();

public slots:
    void changeTeamFilter(int index);
    void changeAttendanceFilter(QModelIndex index);

private:
    Ui::AttendanceTab       *ui;

    TeamModel               *teamModel;
    CategoryModel           *categoryModel;
    AttendanceMatrixModel   *model;
};

#endif // ATTENDANCETAB_H
