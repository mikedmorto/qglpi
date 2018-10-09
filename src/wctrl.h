#ifndef WCTRL_H
#define WCTRL_H

#include <QObject>
#include "def.h"
#include "mwstart.h"

class Wctrl : public QObject
{
    Q_OBJECT

    MWStart * ws;
public:
    explicit Wctrl(QObject *parent = nullptr);
    void start();

signals:

public slots:
    void slotQuit();
};

#endif // WCTRL_H
