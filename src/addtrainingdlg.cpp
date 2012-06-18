#include "addtrainingdlg.h"
#include "ui_addtrainingdlg.h"
#include <QDebug>
#include <QSqlField>
#include <QMessageBox>

/**
 * @brief Creates a dialog for adding and editing training.
 * @param parent The parent widget.
 */
AddTrainingDlg::AddTrainingDlg(TrainingModel *model, int trainingRow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTrainingDlg)
{
    ui->setupUi(this);

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(addTraining()));
    connect(ui->btnAddAndClose, SIGNAL(clicked()), this, SLOT(addTrainingAndClose()));
    connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(saveTraining()));

    teamModel = new TeamModel;
    ui->comboBoxTeam->setModel(teamModel);
    ui->comboBoxTeam->setModelColumn(1);

    this->trainingModel = model;

    QDate currentDate = QDate::currentDate();

    int year = currentDate.year();
    int month = currentDate.month();
    if(month < 9) year--;
    startSeason = QDate::fromString("1.9."+QString::number(year), "d.M.yyyy");
    endSeason = QDate::fromString("31.8."+QString::number(year+1), "d.M.yyyy");

    if(trainingRow == -1) // Add
    {
        ui->editDate->setDate(currentDate);
        ui->btnSave->setVisible(false);
        ui->chckBoxCanceled->setVisible(false);

    }
    else // Edit
    {
        setWindowTitle(tr("Edit training"));

        QSqlRecord record = trainingModel->record(trainingRow);

        QDateTime datetime = record.field("datetime").value().toDateTime();

        int pos = teamModel->getPosition(record.field("team_id").value().toInt());
        ui->comboBoxTeam->setCurrentIndex(pos);

        ui->editDate->setDate(datetime.date());
        ui->editTime->setTime(datetime.time());
        ui->editPlace->setText(record.field("place").value().toString());
        ui->chckBoxCanceled->setChecked(record.field("canceled").value().toBool());

        ui->checkBoxEveryWeek->setVisible(false);
        ui->checkBoxEveryWeek->setChecked(false);
        ui->comboBoxDay->setVisible(false);
        ui->editDate->setEnabled(true);
        ui->btnAdd->setVisible(false);
        ui->btnAddAndClose->setVisible(false);
    }

    m_row = trainingRow;

    setWindowState(Qt::WindowMinimized);
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

void AddTrainingDlg::saveTraining()
{
    if(!checkForm(tr("Edit training"))) return;

    QSqlRecord record = prepareRecords().at(0);

    trainingModel->setRecord(m_row, record);
    trainingModel->submitAll();

    close();
}

bool AddTrainingDlg::insertTrainings()
{
    if(!checkForm(tr("Add training"))) return false;

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
    canceled.setValue(ui->chckBoxCanceled->isChecked());
    teamIDField.setValue(teamID);

    record.append(datetimeField);
    record.append(place);
    record.append(canceled);
    record.append(teamIDField);

    return record;
}

bool AddTrainingDlg::checkForm(QString title)
{
    if(ui->editPlace->text().trimmed() == "")
    {
        QMessageBox::information(this, title, tr("You must specified place."));
        return false;
    }
    return true;
}

/**
 * @brief Destructs the dialog.
 */
AddTrainingDlg::~AddTrainingDlg()
{
    delete ui;
}
