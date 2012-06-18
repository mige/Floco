#include "addtournamentdlg.h"
#include "ui_addtournamentdlg.h"

#include <QDate>
#include <QMessageBox>
#include <QSqlField>
#include <QSqlRecord>

AddTournamentDlg::AddTournamentDlg(TournamentModel *model, int tournamentRow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTournamentDlg)
{
    ui->setupUi(this);

    this->tournamentRow = tournamentRow;
    this->model = model;

    teamModel = new TeamModel;
    ui->comboBox->setModel(teamModel);
    ui->comboBox->setModelColumn(1);

    if(tournamentRow == -1) //ADD
    {
        ui->btnSave->setVisible(false);
        ui->dateEdit->setDate(QDate::currentDate());
    }
    else // EDIT
    {
        setWindowTitle(tr("Edit tournament"));
        ui->btnAdd->setVisible(false);
        ui->btnAddAndClose->setVisible(false);

        QSqlRecord record = model->record(tournamentRow);
        ui->dateEdit->setDate(record.field("date").value().toDate());
        ui->editPlace->setText(record.field("place").value().toString());
        ui->checkBox->setChecked(record.field("season").value().toBool());

        int pos = teamModel->getPosition(record.field("team_id").value().toInt());
        ui->comboBox->setCurrentIndex(pos);
    }

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(addTournament()));
    connect(ui->btnAddAndClose, SIGNAL(clicked()), this, SLOT(addTournamentAndClose()));
    connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(saveEditedTournament()));
}

bool AddTournamentDlg::insertTournament()
{
    if(!checkForm(tr("Add tournament"))) return false;

    QSqlRecord record = createRecord();
    if(!model->insertRecord(-1, record))
        qDebug("err");
    if(!model->submitAll())
        qDebug("err submit");

    return true;
}

QSqlRecord AddTournamentDlg::createRecord()
{
    int idx = ui->comboBox->currentIndex();
    int id = teamModel->record(idx).field("id").value().toInt();

    QSqlRecord record;

    QSqlField date("date", QVariant::Date);
    QSqlField place("place", QVariant::String);
    QSqlField season("season", QVariant::Bool);
    QSqlField teamId("team_id", QVariant::Int);

    date.setValue(ui->dateEdit->date());
    place.setValue(ui->editPlace->text());
    season.setValue(ui->checkBox->isChecked());
    teamId.setValue(id);

    record.append(date);
    record.append(place);
    record.append(season);
    record.append(teamId);

    return record;
}

/**
 * @brief Checks the data from the form and when everything is ok, data is inserted into the model.
 * @sa AddPlayerDlg::addTournamentAndClose()
 */
void AddTournamentDlg::addTournament()
{
    if(insertTournament())
    {
        ui->comboBox->setCurrentIndex(0);
        ui->editPlace->setText("");
        ui->dateEdit->setDate(QDate::currentDate());
        ui->checkBox->setChecked(true);
    }
}

/**
 * @brief Checks the data from the form and when everything is ok, data is inserted into the model and close the dialog.
 * @sa AddPlayerDlg::addTournament()
 */
void AddTournamentDlg::addTournamentAndClose()
{
    if(insertTournament()) close();
}

/**
 * @brief Checks the data from the form and when everything is ok, data is edited in the model and close the dialog.
 */
void AddTournamentDlg::saveEditedTournament()
{
    if(!checkForm(tr("Edit tournament"))) return;

    QSqlRecord record = createRecord();
    model->setRecord(tournamentRow, record);
    model->submitAll();
    close();
}

bool AddTournamentDlg::checkForm(QString title)
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
AddTournamentDlg::~AddTournamentDlg()
{
    delete teamModel;
    delete ui;
}
