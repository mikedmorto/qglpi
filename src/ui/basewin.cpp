#include "basewin.h"

BaseWin::BaseWin(QWidget *parent) : QMainWindow(parent)
{
    setWindowIcon(QIcon("://files/appicon.png"));
    dw = std::unique_ptr<DWait>(new DWait(this));

    connect(&provider, &DataProvider::log,this,&BaseWin::log);
    connect(&provider, &DataProvider::sigProgress, dw.get(), &DWait::setProgress);
    connect(dw.get(),&DWait::sigCancel,&provider,&DataProvider::slotCancel);

    // to close the current window
    this->shcClose = new QShortcut(QKeySequence::Close,this);
    connect(this->shcClose,&QShortcut::activated,this,&BaseWin::close);
}

BaseWin::~BaseWin()
{

}

void BaseWin::start(const LoginItem &login, Config *cfg)
{
    this->currentLogin = login;
    this->cfg = cfg;
    provider.setLogin(this->currentLogin);
    provider.setIgnoreSslCert(cfg->getIgnoreSsl());
    slotStatusBar();

    show();
    raise();
    activateWindow();
}

void BaseWin::slotTerminate()
{
    setVisible(false);
    deleteLater();
}

void BaseWin::slotUpdateSession(const LoginItem &login)
{

}

bool BaseWin::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick and obj->objectName() == "infobar") {
       slotSession();
    }
    return QObject::eventFilter(obj, event);
}

void BaseWin::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void BaseWin::slotAbout()
{
    DiaAbout dia(this);
    dia.exec();
}

void BaseWin::slotError()
{
    QString msg = tr("Critical error - %1").arg(provider.getLastError());
    log(me, MLog::logAlert, QString("Failure %1").arg(msg));
    dw->stop();
    AQP::critical(this, "Error", msg);
}

void BaseWin::slotStatusBar()
{
    // rewrite the status bar
    infobar.clear();
    infobar.setText(tr("I am infobar"));
}

void BaseWin::slotSession()
{
    // there is requests for session status
    slotStatusBar();
}
