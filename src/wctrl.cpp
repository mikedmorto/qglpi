#include "wctrl.h"

Wctrl::Wctrl(QObject *parent) : QObject(parent)
{
    cfg = new Config();
    cfg->load();
    ws = new MWStart(this->cfg);
    mlog = new MLog();
    mlog->setLevel(cfg->getLoglevel());
    mlog->setFile(cfg->getLogfile());
    connect(ws,&MWStart::sigQuit,this,&Wctrl::slotQuit);
    connect(this,&Wctrl::log,mlog,&MLog::slotPut);
    connect(ws,&MWStart::log,mlog,&MLog::slotPut);
}

void Wctrl::start()
{
    log(me,MLog::logInfo,tr("Start application"));
    log(me,MLog::logDebug,tr("Application %1, ").arg(APP_NAME));
    log(me,MLog::logDebug,tr("Version: %1, ").arg(GIT_VERSION));
    log(me,MLog::logDebug,tr("Build timestamp: %1 %2, ").arg(QString(__DATE__)).arg(QString(__TIME__)));
    log(me,MLog::logDebug,tr("Qt version: %1, ").arg(qVersion()));
    log(me,MLog::logDebug,tr("Operation system: %1, %2").arg(QSysInfo::productType()+" "
                 +QSysInfo::productVersion()).arg(QSysInfo::currentCpuArchitecture()));

    ws->show();
}

void Wctrl::slotQuit()
{
    log(me,MLog::logInfo,tr("Quit application"));
    ws->close();
    ws->deleteLater();
    // this is the place for last operations
    // example for save configuration etc
    exit(0);
}
