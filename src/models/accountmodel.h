#ifndef ACCOUNTMODEL_H
#define ACCOUNTMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include "QDebug"

struct LoginItem{
    enum AuthType{
        Password = 0,
        Token = 1
    };
    int authType = Password;
    QString name;
    QString serverurl;
    QString apptoken;
    QString login;
    QString pass;
    QString token;
    QString session_token;
    void imp(const QString &data){
        QStringList sd = data.split(";");
        if(sd.count() != 7 )
            return;
        authType = QString(sd.at(0)).toInt();
        name = sd.at(1);
        serverurl = sd.at(2);;
        apptoken = sd.at(3);;
        login = sd.at(4);;
        pass = sd.at(5);;
        token = sd.at(6);
    }
    QString exp(){
        QString ret;
        ret.append(QString("%1").arg(authType));
        ret.append(";");
        ret.append(name);
        ret.append(";");
        ret.append(serverurl);
        ret.append(";");
        ret.append(apptoken);
        ret.append(";");
        ret.append(login);
        ret.append(";");
        ret.append(pass);
        ret.append(";");
        ret.append(token);
        return ret;
    }
};

class AccountModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    AccountModel();
    void resetData(const QVector<LoginItem> &acclist);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    int itemCount()const;
    void addItem(const LoginItem &item);
    LoginItem getItem(const QModelIndex &index) const;
    LoginItem getItemByInd(int ind)const;
    void deleteItem(const QModelIndex &index);
    void updateItem(const QModelIndex &index, const LoginItem &item);
    QVector<LoginItem> getItems()const;
private:
    QVector<LoginItem> items;
};

#endif // ACCOUNTMODEL_H
