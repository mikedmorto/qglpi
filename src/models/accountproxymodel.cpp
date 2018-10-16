#include "accountproxymodel.h"

AccountProxyModel::AccountProxyModel()
{

}

void AccountProxyModel::setFilter(const QString &filter)
{
    this->filter = filter;
    this->filterChanged();
}

QString AccountProxyModel::getFilter() const
{
    return this->filter;
}

QVariant AccountProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return sourceModel()->headerData(section, orientation,role);
}

bool AccountProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    AccountModel *model = qobject_cast<AccountModel*>(sourceModel());
    for(int i = 0 ; i < model->columnCount(source_parent); i++){
        if(model->data(model->index(source_row, i, source_parent), Qt::DisplayRole)
                .toString().contains(this->filter, Qt::CaseInsensitive)){
            return true;
        }
    }
    return false;
}
