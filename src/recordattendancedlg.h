#ifndef RECORDATTENDANCEDLG_H
#define RECORDATTENDANCEDLG_H

#include <QDialog>
#include <QSqlRecord>
#include <models/attendancemodel.h>

namespace Ui {
class RecordAttendanceDlg;
}

class RecordAttendanceDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit RecordAttendanceDlg(QSqlRecord record, QWidget *parent = 0);
    ~RecordAttendanceDlg();
    
private:
    Ui::RecordAttendanceDlg *ui;
    AttendanceModel         *attendanceModel;
};

#endif // RECORDATTENDANCEDLG_H
