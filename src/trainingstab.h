#ifndef TRAININGSTAB_H
#define TRAININGSTAB_H

#include <QWidget>

namespace Ui {
    class TrainingsTab;
}

class TrainingsTab : public QWidget
{
    Q_OBJECT

public:
    explicit TrainingsTab(QWidget *parent = 0);
    ~TrainingsTab();

private:
    Ui::TrainingsTab *ui;
};

#endif // TRAININGSTAB_H
