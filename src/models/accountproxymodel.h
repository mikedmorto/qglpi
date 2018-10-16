#ifndef ACCOUNTPROXYMODEL_H
#define ACCOUNTPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include "accountmodel.h"

class AccountProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    AccountProxyModel();
    void setFilter(const QString &filter);
    QString getFilter() const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    QString filter;
};

#endif // ACCOUNTPROXYMODEL_H
