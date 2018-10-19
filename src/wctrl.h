#ifndef WCTRL_H
#define WCTRL_H

#include <QObject>
#include "def.h"
#include "mwstart.h"
#include "mwmain.h"

class Wctrl : public QObject
{
    Q_OBJECT

    MWStart * ws;
    Config * cfg;
    MLog * mlog;
    QString me = "Wctrl";
    LoginItem currentLogin;
    MWMain mainw;

    void startMWMain();

public:
    explicit Wctrl(QObject *parent = nullptr);
    void start();

signals:
    void log(const QString &,MLog::LogLevel,const QString &);
public slots:
    void slotQuit();
private slots:
    void slotAuthDone();
};

#endif // WCTRL_H
