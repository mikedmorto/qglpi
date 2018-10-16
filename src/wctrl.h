#ifndef WCTRL_H
#define WCTRL_H

#include <QObject>
#include "def.h"
#include "mwstart.h"

class Wctrl : public QObject
{
    Q_OBJECT

    MWStart * ws;
    Config * cfg;
    MLog * mlog;
    QString me = "Wctrl";
public:
    explicit Wctrl(QObject *parent = nullptr);
    void start();

signals:
    void log(const QString &,MLog::LogLevel,const QString &);
public slots:
    void slotQuit();
};

#endif // WCTRL_H
