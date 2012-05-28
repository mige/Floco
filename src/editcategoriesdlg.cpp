#include "editcategoriesdlg.h"
#include "ui_editcategoriesdlg.h"

#include <QMessageBox>

//!

EditCategoriesDlg::EditCategoriesDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditCategoriesDlg)
{    
    ui->setupUi(this);

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(showAddCategoryDlg()));
    connect(ui->btnDelete, SIGNAL(clicked()), this, SLOT(deleteCategory()));
    connect(ui->btnEdit, SIGNAL(clicked()), this, SLOT(showEditCategoryDlg()));
    connect(ui->radioMale, SIGNAL(toggled(bool)), this, SLOT(changeSex(bool)));

    model = new CategoryModel(this);
    model->setFilter("male='true'");

    ui->treeView->setModel(model);
    ui->treeView->hideColumn(0);
    ui->treeView->hideColumn(2);
}

//! Change sex for the filter categories.
/*!
  \param male boolean True if the male
*/
void EditCategoriesDlg::changeSex(bool male)
{
    if(male) model->setFilter("male='true'");
    else model->setFilter("male='false'");
}

//! Delete the selected category
void EditCategoriesDlg::deleteCategory()
{
    QItemSelectionModel *selmodel = ui->treeView->selectionModel();
    QModelIndexList list = selmodel->selectedIndexes();

    if(list.size() > 0)
        if(QMessageBox::question(this, tr("Delete category"), tr("Really delete category?"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::No) return;

    for(int i = 0; i < list.size(); i++)
        model->removeRow(list.at(i).row());
    model->submitAll();
}

//! Show dialog for add category.
void EditCategoriesDlg::showAddCategoryDlg()
{
    addCategoryDlg = new AddCategoryDlg(model);
    addCategoryDlg->exec();
    delete addCategoryDlg;
}

//! Show dialog for edit category.
void EditCategoriesDlg::showEditCategoryDlg()
{
    QItemSelectionModel *selmodel = ui->treeView->selectionModel();
    QModelIndexList list = selmodel->selectedIndexes();

    if(list.size() > 0)
    {
        addCategoryDlg = new AddCategoryDlg(model, list.at(0).row());
        addCategoryDlg->exec();
        delete addCategoryDlg;
    }
}

//! The destructor.
EditCategoriesDlg::~EditCategoriesDlg()
{
    delete model;
    delete ui;
}
