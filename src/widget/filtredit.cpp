#include "filtredit.h"

#include <QStyle>

/**
 * @brief Creates a line edit widget with <i>Filter...</i> text and clear button.
 *
 * The <i>Filter...</i> text hides, if user wrote something and shows, when line edit is epmty.
 * @param parent Parent widget.
 */
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

/**
 * @brief Reimplemented from QLineEdit::focusInEvent().
 *
 * Remove the <i>Filter...</i> text.
 * @param e Event.
 */
void FiltrEdit::focusInEvent(QFocusEvent *e)
{
    if(text() == tr("Filter..."))
    {
        setText("");
        setStyleSheet("font-style: normal;");
    }
    QLineEdit::focusInEvent(e);
}

/**
 * @brief Reimplemented from QLineEdit::focusOutEvent().
 *
 * Set the <i>Filter...</i> text.
 * @param e Event.
 */
void FiltrEdit::focusOutEvent(QFocusEvent *e)
{
    if(text().trimmed() == "")
    {
        setStyleSheet("font-style: italic;");
        setText(tr("Filter..."));
    }
    QLineEdit::focusOutEvent(e);
}

/**
 * @brief Reimplemented from QLineEdit::resizeEvent().
 *
 * When resize moves the clear button to the correct position.
 * @param e Event.
 */
void FiltrEdit::resizeEvent(QResizeEvent *e)
{
    QSize sz = clearButton->sizeHint();
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    clearButton->move(rect().right() - frameWidth - sz.width(),
                       (rect().bottom() + 1 - sz.height())/2);
    QLineEdit::resizeEvent(e);
}

/**
 * @brief Shows/hides clear button.
 * @param text Text in the filter edit.
 */
void FiltrEdit::updateCloseButton(const QString& text)
{
    if(text.isEmpty() || text == tr("Filter..."))
        clearButton->setVisible(false);
    else
        clearButton->setVisible(true);
}
