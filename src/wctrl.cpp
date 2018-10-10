#include "wctrl.h"

Wctrl::Wctrl(QObject *parent) : QObject(parent)
{
    cfg = new Config();
    cfg->load();
    ws = new MWStart(this->cfg);
    connect(ws,&MWStart::sigQuit,this,&Wctrl::slotQuit);
}

void Wctrl::start()
{
    ws->show();
}

void Wctrl::slotQuit()
{
    ws->close();
    ws->deleteLater();
    // this is the place for last operations
    // example for save configuration etc
    exit(0);
}
