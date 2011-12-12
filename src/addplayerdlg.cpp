#include "addplayerdlg.h"
#include "ui_addplayerdlg.h"

#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlField>
#include <QDebug>

AddPlayerDlg::AddPlayerDlg(QSqlTableModel *model, int playerId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPlayerDlg)
{
    ui->setupUi(this);

    this->model = model;

    if(playerId == -1)
    {
        ui->btnSave->setVisible(false);
    }
    else
    {
        ui->btnAdd->setVisible(false);
        ui->btnAddAndClose->setVisible(false);

        // TODO: výběr položky a doplnění do formuláře
    }

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(addPlayer()));
    connect(ui->btnAddAndClose, SIGNAL(clicked()), this, SLOT(addPlayerAndClose()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
}

bool AddPlayerDlg::insertPlayer()
{
    if(ui->editFirstname->text().trimmed() == "" ||
       ui->editSurname->text().trimmed() == "")
    {
        QMessageBox::information(this, tr("Add player"), tr("You must specified firstname and surname."));
        return false;
    }

    model->setTable("player");
    model->select();

    QSqlRecord record;

    QSqlField firstname("firstname", QVariant::String);
    QSqlField surname("surname", QVariant::String);
    QSqlField birth("birth", QVariant::Date);
    QSqlField address("address", QVariant::String);
    QSqlField email("email", QVariant::String);
    QSqlField phone("phone", QVariant::String);
    QSqlField number("number", QVariant::Int);
    QSqlField post("post", QVariant::String);

    firstname.setValue(ui->editFirstname->text().trimmed());
    surname.setValue(ui->editSurname->text().trimmed());
    birth.setValue(ui->editDayOfBirth->date());
    address.setValue(ui->editAddress->text().trimmed());
    email.setValue(ui->editEmail->text().trimmed());
    phone.setValue(ui->editPhone->text().trimmed());
    number.setValue(ui->spinNumber->value());
    post.setValue(ui->comboPost->currentText());

    record.append(firstname);
    record.append(surname);
    record.append(address);
    record.append(birth);
    record.append(email);
    record.append(phone);
    record.append(number);
    record.append(post);

    if(!model->insertRecord(-1, record))
        qDebug("err");
    if(!model->submitAll())
        qDebug("err submit");

    return true;
}

void AddPlayerDlg::addPlayer()
{
    if(insertPlayer())
    {
        ui->editFirstname->setText("");
        ui->editSurname->setText("");
        ui->editAddress->setText("");
        ui->editEmail->setText("");
        ui->editPhone->setText("");
        ui->spinNumber->setValue(1);
        ui->comboPost->setCurrentIndex(0);
    }
}

void AddPlayerDlg::addPlayerAndClose()
{
    if(insertPlayer()) close();
}

AddPlayerDlg::~AddPlayerDlg()
{
    delete ui;
}
