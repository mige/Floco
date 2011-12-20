#include "addplayerdlg.h"
#include "ui_addplayerdlg.h"

#include <QBuffer>
#include <QFile>
#include <QFileDialog>
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
    this->idPlayer = playerId;

    if(playerId == -1)
    {
        ui->btnSave->setVisible(false);
    }
    else
    {
        ui->btnAdd->setVisible(false);
        ui->btnAddAndClose->setVisible(false);

        QSqlRecord record = model->record(playerId);

        ui->editFirstname->setText(record.field("firstname").value().toString());
        ui->editSurname->setText(record.field("surname").value().toString());
        ui->editAddress->setText(record.field("address").value().toString());
        ui->editEmail->setText(record.field("email").value().toString());
        ui->editPhone->setText(record.field("phone").value().toString());
        ui->editDayOfBirth->setDate(record.field("birth").value().toDate());
        ui->spinNumber->setValue(record.field("number").value().toInt());

        QString post = record.field("post").value().toString();

        if(post == "defender") ui->comboPost->setCurrentIndex(0);
        else if(post == "forward") ui->comboPost->setCurrentIndex(1);
        else ui->comboPost->setCurrentIndex(2);
    }

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(addPlayer()));
    connect(ui->btnAddAndClose, SIGNAL(clicked()), this, SLOT(addPlayerAndClose()));
    connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(saveEditedPlayer()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnFile, SIGNAL(clicked()), this, SLOT(selectFile()));
}

bool AddPlayerDlg::insertPlayer()
{
    if(!checkForm(tr("Add player"))) return false;

    QSqlRecord record = createRecord();
    if(!model->insertRecord(-1, record))
        qDebug("err");
    if(!model->submitAll())
        qDebug("err submit");

    return true;
}

QSqlRecord AddPlayerDlg::createRecord()
{
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

    QString fileName = ui->editFile->text().trimmed();
    if(fileName != "")
    {
        QPixmap pixmap(fileName);
        pixmap = pixmap.scaledToWidth(128, Qt::SmoothTransformation);
        QByteArray bytes;
        QBuffer buffer(&bytes);
        buffer.open(QIODevice::WriteOnly);
        pixmap.save(&buffer, fileName.split(".").last().toAscii());
        buffer.close();

        QSqlField photo("photo", QVariant::ByteArray);
        photo.setValue(bytes);
        record.append(photo);
    }

    return record;
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

void AddPlayerDlg::saveEditedPlayer()
{
    if(!checkForm(tr("Edit player"))) return;

    QSqlRecord record = createRecord();
    model->setRecord(idPlayer, record);
    model->submitAll();
    close();
}

bool AddPlayerDlg::checkForm(QString formName)
{
    if(ui->editFirstname->text().trimmed() == "" ||
       ui->editSurname->text().trimmed() == "")
    {
        QMessageBox::information(this, formName, tr("You must specified firstname and surname."));
        return false;
    }

    QString fileName = ui->editFile->text().trimmed();

    QFile file(fileName);

    if(!file.exists() && fileName != "")
    {
        QMessageBox::information(this, tr("Add player"), tr("Selected file does not exists."));
        return false;
    }

    return true;
}

void AddPlayerDlg::selectFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/home/mige", tr("Image Files (*.png *.jpg *.bmp)"));

    ui->editFile->setText(fileName);
}

AddPlayerDlg::~AddPlayerDlg()
{
    delete ui;
}
