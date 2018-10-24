#ifndef BASEWIN_H
#define BASEWIN_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QShortcut>
#include "accountmodel.h"
#include "mlog.h"
#include "dataprovider.h"
#include "dwait.h"
#include "diaabout.h"
#include "aqp.hpp"
#include "diaentitieslist.h"

class BaseWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit BaseWin(QWidget *parent = nullptr);
    ~BaseWin();
    virtual void start(const LoginItem &login,Config * cfg);
    virtual void slotTerminate();
    virtual void slotUpdateSession(const LoginItem &login);

protected:

    LoginItem currentLogin;
    DataProvider provider;
    std::unique_ptr<DWait> dw;
    Config * cfg;
    QLabel infobar;
    QShortcut * shcClose;
    const QString me = "";


    bool eventFilter(QObject *obj, QEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

    void slotAbout();
    void slotError();
    void slotStatusBar();
    void slotSession();

signals:
    void log(const QString &,MLog::LogLevel,const QString &);
public slots:
};

#endif // BASEWIN_H
