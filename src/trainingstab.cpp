#include "trainingstab.h"
#include "ui_trainingstab.h"

TrainingsTab::TrainingsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrainingsTab)
{
    ui->setupUi(this);
}

TrainingsTab::~TrainingsTab()
{
    delete ui;
}
