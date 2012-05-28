#ifndef CATEGORYMODEL_H
#define CATEGORYMODEL_H

#include <QSqlTableModel>

/**
 * @brief The CategoryModel class provides the categories of players model from the database.
 */
class CategoryModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit CategoryModel(QObject *parent = 0);
    QVariant data(const QModelIndex &item, int role) const;
    QList<QString> categoryList();

signals:

public slots:

};

#endif // CATEGORYMODEL_H
