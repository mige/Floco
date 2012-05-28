#ifndef FILTREDIT_H
#define FILTREDIT_H

#include <QLineEdit>
#include <QToolButton>

/**
 * @brief The FiltrEdit widget provides fields for filtering results.
 */
class FiltrEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit FiltrEdit(QWidget *parent = 0);

protected:
    virtual void focusInEvent(QFocusEvent *);
    virtual void focusOutEvent(QFocusEvent *);

    void resizeEvent(QResizeEvent *);

private slots:
    void updateCloseButton(const QString &text);

private:
    QToolButton *clearButton;
};

#endif // FILTREDIT_H
