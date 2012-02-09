#ifndef ADDCATEGORYDLG_H
#define ADDCATEGORYDLG_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
    class AddCategoryDlg;
}

class AddCategoryDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddCategoryDlg(QSqlTableModel *categoryModel, int categoryId = -1, QWidget *parent = 0);
    ~AddCategoryDlg();

public slots:
    void addCategory();
    void addCategoryAndClose();
    void editCategory();

private:
    bool        insertCategory();
    bool        checkForm(QString formName);
    QSqlRecord  createRecord();

    Ui::AddCategoryDlg  *ui;
    QSqlTableModel      *model;
    int                 idCategory;
};

#endif // ADDCATEGORYDLG_H
