#include "recordattendancedlg.h"
#include "ui_recordattendancedlg.h"

#include <QDateTime>
#include <QSqlField>
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

    QDateTime datetime = record.field("datetime").value().toDateTime();
    ui->txtTrainingDatetime->setText(datetime.toString(tr("dd.MM.yyyy h:mm")));
}

RecordAttendanceDlg::~RecordAttendanceDlg()
{
    delete ui;
}
