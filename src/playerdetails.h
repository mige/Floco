#ifndef PLAYERDETAILS_H
#define PLAYERDETAILS_H

#include <QDialog>
#include <QSqlRecord>

namespace Ui {
class PlayerDetails;
}

class PlayerDetails : public QDialog
{
    Q_OBJECT
    
public:
    explicit PlayerDetails(QSqlRecord record,QWidget *parent = 0);
    ~PlayerDetails();
    
private:
    Ui::PlayerDetails *ui;
};

#endif // PLAYERDETAILS_H
