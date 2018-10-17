#include "accountmodel.h"

AccountModel::AccountModel()
{

}

void AccountModel::resetData(const QVector<LoginItem> &acclist)
{
    beginResetModel();
    items.clear();
    this->items = acclist;
    endResetModel();
}

int AccountModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return items.count();
}

int AccountModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant AccountModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= items.count())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        switch (index.column()) {
        case 0:
            return items.at(index.row()).name;
        default:
            return QVariant();
        }
    case Qt::ToolTipRole:
        return QVariant();
    }
    return QVariant();
}

QVariant AccountModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case 0:
            return tr("Name");
        default:
            return QVariant();
        }
    }
    if (orientation == Qt::Vertical && role == Qt::DisplayRole) {
        return section + 1;
    }
    return QVariant();
}

int AccountModel::itemCount() const
{
    return this->items.count();
}

void AccountModel::addItem(const LoginItem &item)
{
    beginResetModel();
    this->items.append(item);
    endResetModel();
}

LoginItem AccountModel::getItem(const QModelIndex &index) const
{
    if(index.isValid() && index.row() <= items.count())
        return this->items.at(index.row());
    return LoginItem();
}

LoginItem AccountModel::getItemByInd(int ind) const
{
    if(ind <0 or ind > this->items.count())
        return LoginItem();
    return this->items.at(ind);
}

void AccountModel::deleteItem(const QModelIndex &index)
{
    if(!index.isValid())
        return;
    this->beginRemoveRows(QModelIndex(),index.row(),index.row());
    LoginItem item =  this->items.takeAt(index.row());
    this->endRemoveRows();
}

void AccountModel::updateItem(const QModelIndex &index, const LoginItem &item)
{
    if(!index.isValid())
        return;
    this->items.replace(index.row(),item);
    this->dataChanged(index,index);
}

QVector<LoginItem> AccountModel::getItems() const
{
    return this->items;
}
