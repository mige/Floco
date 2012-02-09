#include "addcategorydlg.h"
#include "ui_addcategorydlg.h"

#include <QMessageBox>
#include <QSqlField>
#include <QSqlRecord>

AddCategoryDlg::AddCategoryDlg(QSqlTableModel *categoryModel, int categoryId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCategoryDlg)
{
    ui->setupUi(this);

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(addCategory()));
    connect(ui->btnAddAndClose, SIGNAL(clicked()), this, SLOT(addCategoryAndClose()));
    connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(editCategory()));

    model = categoryModel;
    idCategory = categoryId;

    if(idCategory == -1)
        ui->btnSave->setVisible(false);
    else
    {
        ui->btnAdd->setVisible(false);
        ui->btnAddAndClose->setVisible(false);
        this->setWindowTitle(tr("Edit category"));

        QSqlRecord record = model->record(idCategory);

        ui->txtName->setText(record.field("name").value().toString());
        int maxAge = record.field("max_age").value().toInt();
        if(maxAge == 100)
            ui->checkBoxAdult->setChecked(true);
        else
            ui->spinBoxMaxAge->setValue(maxAge);
        if(!record.field("male").value().toBool())
            ui->radioFemale->setChecked(true);
    }
}

void AddCategoryDlg::addCategory()
{
    if(insertCategory())
    {
        ui->txtName->setText("");
        ui->radioMale->setChecked(true);
        ui->spinBoxMaxAge->setValue(5);
        ui->checkBoxAdult->setChecked(false);
    }
}

void AddCategoryDlg::addCategoryAndClose()
{
    if(insertCategory()) close();
}

void AddCategoryDlg::editCategory()
{
    if(!checkForm(tr("Edit category"))) return;

    QSqlRecord record = createRecord();
    model->setRecord(idCategory, record);
    model->submitAll();
    close();
}

bool AddCategoryDlg::insertCategory()
{
    if(!checkForm(tr("Add category"))) return false;

    QSqlRecord record = createRecord();
    if(!model->insertRecord(-1, record))
        qDebug("err");
    if(!model->submitAll())
        qDebug("err submit");

    return true;
}

QSqlRecord AddCategoryDlg::createRecord()
{
    QSqlRecord record;

    QSqlField name("name", QVariant::String);
    QSqlField male("male", QVariant::Bool);
    QSqlField maxAge("max_age", QVariant::Int);

    name.setValue(ui->txtName->text().trimmed());

    if(ui->radioMale->isChecked())
        male.setValue(true);
    else
        male.setValue(false);

    if(ui->checkBoxAdult->isChecked())
        maxAge.setValue(100);
    else
        maxAge.setValue(ui->spinBoxMaxAge->value());

    record.append(name);
    record.append(male);
    record.append(maxAge);

    return record;
}

bool AddCategoryDlg::checkForm(QString formName)
{
    if(ui->txtName->text().trimmed() == "")
    {
        QMessageBox::information(this, formName, tr("You must specified category name."));
        return false;
    }
    return true;
}

AddCategoryDlg::~AddCategoryDlg()
{
    delete ui;
}
