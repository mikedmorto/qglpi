#ifndef MWSTART_H
#define MWSTART_H

#include <QMainWindow>
#include "diaabout.h"
#include "diapreferences.h"
#include "diaaccounts.h"
#include "dwait.h"
#include "dataprovider.h"
#include "aqp.hpp"
#include "accountproxymodel.h"

namespace Ui {
class MWStart;
}

class MWStart : public QMainWindow
{
    Q_OBJECT
    Config * cfg;
    Ui::MWStart *ui;
    DWait * dw;
    DataProvider provider;
    QString me = "MWStart";
    AccountModel model;
    AccountProxyModel proxy;
    LoginItem currentLogin;
public:
    explicit MWStart(Config * cfg, QWidget *parent = nullptr);
    ~MWStart();
    LoginItem getLogin();

signals:
    void sigQuit();
    void log(const QString &,MLog::LogLevel,const QString &);
    void sigAuthDone();
private slots:
    void slotQuit();
    void slotAbout();
    void slotPreferences();
    void slotConnect();
    void slotAccounts();
};

#endif // MWSTART_H
