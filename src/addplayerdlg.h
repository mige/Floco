#ifndef ADDPLAYERDLG_H
#define ADDPLAYERDLG_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
    class AddPlayerDlg;
}

/**
 * @brief The AddPlayerDlg class provides the window for adding or editing players.
 */
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
    void selectFile();

private:
    bool        insertPlayer();
    QSqlRecord  createRecord();
    bool        checkForm(QString formName);

    Ui::AddPlayerDlg    *ui;
    QSqlTableModel      *model;
    int                 idPlayer;
};

#endif // ADDPLAYERDLG_H
