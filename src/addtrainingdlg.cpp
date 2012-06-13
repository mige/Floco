#include "addtrainingdlg.h"
#include "ui_addtrainingdlg.h"
#include <QDebug>
#include <QSqlField>
#include <databasemanager.h>

/**
 * @brief Creates a dialog for adding and editing training.
 * @param parent The parent widget.
 */
AddTrainingDlg::AddTrainingDlg(TrainingModel *model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTrainingDlg)
{
    ui->setupUi(this);

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(addTraining()));
    connect(ui->btnAddAndClose, SIGNAL(clicked()), this, SLOT(addTrainingAndClose()));

    teamModel = new TeamModel;
    ui->comboBoxTeam->setModel(teamModel);
    ui->comboBoxTeam->setModelColumn(1);

    this->trainingModel = model;

    int year = QDate::currentDate().year();
    int month = QDate::currentDate().month();
    if(month < 9) year--;
    startSeason = QDate::fromString("1.9."+QString::number(year), "d.M.yyyy");
    endSeason = QDate::fromString("31.8."+QString::number(year+1), "d.M.yyyy");
}

void AddTrainingDlg::addTraining()
{
    if(!insertTrainings()) return;

    ui->checkBoxEveryWeek->setChecked(true);
    ui->editDate->setEnabled(false);
    ui->editTime->setTime(QTime::fromString("12:00", "hh:mm"));
    ui->editPlace->setText("");
}

void AddTrainingDlg::addTrainingAndClose()
{
    if(!insertTrainings()) return;

    close();
}

bool AddTrainingDlg::insertTrainings()
{
    if(false) return false; // TODO: checkk form

    QList<QSqlRecord> records = prepareRecords();

    if(records.size() == 0) return false;

    QList<QSqlRecord>::iterator r;
    for(r = records.begin(); r != records.end(); ++r)
    {
        if(!trainingModel->insertRecord(-1, *r))
            qDebug("err insert record");
    }

    if(!trainingModel->submitAll())
    {
        qDebug() << records;
        qDebug() << DatabaseManager::getInstance()->lastError();
        qDebug("err submit");
    }

    return true;
}

QList<QSqlRecord> AddTrainingDlg::prepareRecords()
{
    QList<QSqlRecord> records;
    int idx = ui->comboBoxTeam->currentIndex();
    int teamId = teamModel->record(idx).field("id").value().toInt();
    if(ui->checkBoxEveryWeek->isChecked())
    {
        QDateTime start = QDateTime::currentDateTime();
        start.setTime(ui->editTime->time());
        int nowDayOfWeek = start.date().dayOfWeek();
        int dayOfWeek = ui->comboBoxDay->currentIndex()+1;

        if(dayOfWeek > nowDayOfWeek)
            start = start.addDays(dayOfWeek - nowDayOfWeek);
        else if(dayOfWeek < nowDayOfWeek)
            start = start.addDays(dayOfWeek - nowDayOfWeek + 7);

        while(start.date() < endSeason)
        {
            records.append(createRecord(start, teamId));
            start = start.addDays(7);
        }
    }
    else
    {
        QDateTime datetime = ui->editDate->dateTime();
        datetime.setTime(ui->editTime->time());
        records.append(createRecord(datetime, teamId));
    }

    return records;
}

QSqlRecord AddTrainingDlg::createRecord(QDateTime datetime, int teamID)
{
    QSqlRecord record;

    QSqlField datetimeField("datetime", QVariant::Date);
    QSqlField place("place", QVariant::String);
    QSqlField canceled("canceled", QVariant::Bool);
    QSqlField teamIDField("team_id", QVariant::Int);

    datetimeField.setValue(datetime);
    place.setValue(ui->editPlace->text().trimmed());
    canceled.setValue(false);
    teamIDField.setValue(teamID);

    record.append(datetimeField);
    record.append(place);
    record.append(canceled);
    record.append(teamIDField);

    return record;
}

/**
 * @brief Destructs the dialog.
 */
AddTrainingDlg::~AddTrainingDlg()
{
    delete ui;
}
