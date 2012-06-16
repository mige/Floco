#include "recordattendancedlg.h"
#include "ui_recordattendancedlg.h"

#include <models/trainingmodel.h>

RecordAttendanceDlg::RecordAttendanceDlg(QSqlRecord record, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordAttendanceDlg)
{
    ui->setupUi(this);

    attendanceModel = new AttendanceModel(record);

    ui->treeView->setModel(attendanceModel);

    connect(ui->btnSave, SIGNAL(clicked()), attendanceModel, SLOT(saveData()));
    connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(close()));
    //QString trainingDatetime = new TrainingModel().filter()
}

RecordAttendanceDlg::~RecordAttendanceDlg()
{
    delete ui;
}
