#include "filtredit.h"

#include <QStyle>

FiltrEdit::FiltrEdit(QWidget *parent) :
    QLineEdit(parent)
{
    clearButton = new QToolButton(this);
    QPixmap pixmap(":/icons/icons/clear-16.png");
    clearButton->setIcon(QIcon(pixmap));
    clearButton->setIconSize(pixmap.size());
    clearButton->setCursor(Qt::ArrowCursor);
    clearButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");
    clearButton->hide();

    connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
    connect(this, SIGNAL(textChanged(const QString&)), this, SLOT(updateCloseButton(const QString&)));

    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    setStyleSheet(QString("QLineEdit { padding-right: %1px; } ").arg(clearButton->sizeHint().width() + frameWidth + 1));
    QSize msz = minimumSizeHint();
    setMinimumSize(qMax(msz.width(), clearButton->sizeHint().height() + frameWidth * 2 + 2),
                   qMax(msz.height(), clearButton->sizeHint().height() + frameWidth * 2 + 2));
}

void FiltrEdit::focusInEvent(QFocusEvent *e)
{
    if(text() == tr("Filter..."))
    {
        setText("");
        setStyleSheet("font-style: normal;");
    }
    QLineEdit::focusInEvent(e);
}

void FiltrEdit::focusOutEvent(QFocusEvent *e)
{
    if(text().trimmed() == "")
    {
        setStyleSheet("font-style: italic;");
        setText(tr("Filter..."));
    }
    QLineEdit::focusOutEvent(e);
}

void FiltrEdit::resizeEvent(QResizeEvent *e)
{
    QSize sz = clearButton->sizeHint();
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    clearButton->move(rect().right() - frameWidth - sz.width(),
                       (rect().bottom() + 1 - sz.height())/2);
    QLineEdit::resizeEvent(e);
}

void FiltrEdit::updateCloseButton(const QString& text)
{
    if(text.isEmpty() || text == tr("Filter..."))
        clearButton->setVisible(false);
    else
        clearButton->setVisible(true);
}
