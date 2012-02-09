#ifndef ATTENDANCETAB_H
#define ATTENDANCETAB_H

#include <QWidget>

namespace Ui {
    class AttendanceTab;
}

class AttendanceTab : public QWidget
{
    Q_OBJECT

public:
    explicit AttendanceTab(QWidget *parent = 0);
    ~AttendanceTab();

private:
    Ui::AttendanceTab *ui;
};

#endif // ATTENDANCETAB_H
