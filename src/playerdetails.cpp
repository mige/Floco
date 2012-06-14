#include "playerdetails.h"
#include "ui_playerdetails.h"

#include <QDate>
#include <QSqlField>

PlayerDetails::PlayerDetails(QSqlRecord record, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerDetails)
{
    ui->setupUi(this);

    setModal(false);

    QString playerName = record.field("firstname").value().toString()+" "+record.field("surname").value().toString();

    setWindowTitle(tr("Player details - ") + playerName);

    ui->txtPlayerName->setText(playerName);
    ui->txtNumber->setText(tr("Number: <b>")+QString::number(record.field("number").value().toInt()));
    ui->txtPost->setText(tr("Post: <b>")+record.field("post").value().toString());
    ui->txtBirth->setText(tr("Day of birth: <b>")+record.field("birth").value().toDate().toString("d.M.yyyy"));
    ui->txtAddress->setText(tr("Address: <b>")+record.field("address").value().toString());
    ui->txtPhone->setText(tr("Phone: <b>")+record.field("phone").value().toString());
    ui->txtMail->setText(tr("E-mail: <b>")+record.field("email").value().toString());

    QByteArray photoData = record.field("photo").value().toByteArray();
    QPixmap photo;

    if(photoData.isNull()) photo.load(":/icons/icons/player-128.png");
    else photo.loadFromData(record.field("photo").value().toByteArray());

    ui->photo->setPixmap(photo);
}

PlayerDetails::~PlayerDetails()
{
    delete ui;
}
