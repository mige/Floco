#ifndef EDITCATEGORIESDLG_H
#define EDITCATEGORIESDLG_H

#include <QDialog>
#include <addcategorydlg.h>
#include <models/categorymodel.h>

namespace Ui {
    class EditCategoriesDlg;
}

class EditCategoriesDlg : public QDialog
{
    Q_OBJECT

public:
    explicit EditCategoriesDlg(QWidget *parent = 0);
    ~EditCategoriesDlg();

public slots:
    void showAddCategory();
    void changeSex(bool male);
    void deleteCategory();
    void editCategory();

private:
    Ui::EditCategoriesDlg   *ui;
    AddCategoryDlg          *addCategoryDlg;
    CategoryModel           *model;
};

#endif // EDITCATEGORIESDLG_H
