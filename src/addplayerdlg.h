#ifndef ADDPLAYERDLG_H
#define ADDPLAYERDLG_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
    class AddPlayerDlg;
}

class AddPlayerDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddPlayerDlg(QSqlTableModel *model, int playerId = -1, QWidget *parent = 0);
    ~AddPlayerDlg();

public slots:
    void addPlayer();
    void addPlayerAndClose();
    void saveEditedPlayer();

private:
    bool insertPlayer();
    QSqlRecord createRecord();

    Ui::AddPlayerDlg *ui;
    QSqlTableModel *model;
    int idPlayer;
};

#endif // ADDPLAYERDLG_H
