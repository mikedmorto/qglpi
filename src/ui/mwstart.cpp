#include "mwstart.h"
#include "ui_mwstart.h"

MWStart::MWStart(Config *cfg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MWStart)
{
    ui->setupUi(this);
    this->cfg = cfg;
    this->ui->statusbar->setHidden(true);
    QPixmap pix("://files/appicon.png");
    ui->lbl_icon->setPixmap(pix.scaled(128,128,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    this->dw = new DWait(this);
    this->proxy.setSourceModel(&model);
    this->cfg->load();
    model.resetData(this->cfg->getLogins());
    this->ui->cb_server->setModel(&model);
    connect(this->dw,&DWait::sigCancel,&provider,&DataProvider::slotCancel);
    connect(&this->provider,&DataProvider::log,this,&MWStart::log);
    connect(this->ui->btn_quit,&QPushButton::clicked,this,&MWStart::slotQuit);
    connect(this->ui->btn_about,&QPushButton::clicked,this,&MWStart::slotAbout);
    connect(this->ui->btn_preferences,&QPushButton::clicked,this,&MWStart::slotPreferences);
    connect(this->ui->btn_connect,&QPushButton::clicked,this,&MWStart::slotConnect);
    connect(this->ui->btn_accounts,&QPushButton::clicked,this,&MWStart::slotAccounts);
}

MWStart::~MWStart()
{
    delete ui;
}

LoginItem MWStart::getLogin()
{
    return this->currentLogin;
}

void MWStart::slotQuit()
{
    this->sigQuit();
}

void MWStart::slotAbout()
{
    DiaAbout dia(this);
    dia.exec();
}

void MWStart::slotPreferences()
{
    DiaPreferences dia(cfg,this);
    if(dia.exec() != QDialog::Accepted)
        return;


}

void MWStart::slotConnect()
{
    int ind = this->ui->cb_server->currentIndex();
    LoginItem item = model.getItemByInd(ind);
    if(item.name.isEmpty()){
        AQP::information(this, "Info", tr("The account list is empty. Please add a new account."));
        return;
    }
    // try auth
    this->provider.setIgnoreSslCert(cfg->getIgnoreSsl());
    log(me,MLog::logDebug,tr("Try auth"));
    dw->start(tr("Connecting to \"%1\"").arg(item.name));
    if( !provider.auth(item) or dw->tryStopState() ){
        QString msg = tr("Error: %1").arg(provider.getLastError());
        log(me, MLog::logAlert, QString("Failure auth. %1").arg(msg));
        dw->stop();
        AQP::critical(this, "Error", msg);
        return;
    }
    log(me, MLog::logInfo, QString("Success auth"));
    dw->stop();
    // auth done, test session_token

    QString result = provider.getResult();
    QJsonObject object = QJsonDocument::fromJson(result.toUtf8()).object();
    QString stok = object["session_token"].toString();
    item.session_token = stok;

    if (stok.isEmpty()){
        QString msg = tr("Error: Session token is empty");
        AQP::critical(this, "Error", msg);
    }else{
        AQP::information(this, "Info", tr("Session token is %1").arg(stok));
    }

    this->currentLogin = item;


    this->provider.setLogin(item);
    // testing getFullSession procedure
    log(me,MLog::logDebug,tr("Try getMyProfiles"));
    dw->start(tr("getFullSession"));
    if( !provider.getFullSession() or dw->tryStopState() ){
        QString msg = tr("Error: %1").arg(provider.getLastError());
        log(me, MLog::logAlert, QString("Failure. %1").arg(msg));
        dw->stop();
        AQP::critical(this, "Error", msg);
        return;
    }
    log(me, MLog::logInfo, QString("Success getFullSession"));
    dw->stop();



    // testing logout procedure
    log(me,MLog::logDebug,tr("Try logout"));
    dw->start(tr("Logout from \"%1\"").arg(item.name));
    if( !provider.logout() or dw->tryStopState() ){
        QString msg = tr("Error: %1").arg(provider.getLastError());
        log(me, MLog::logAlert, QString("Failure. %1").arg(msg));
        dw->stop();
        AQP::critical(this, "Error", msg);
        return;
    }
    log(me, MLog::logInfo, QString("Success logout"));
    dw->stop();
    sigAuthDone();

}

void MWStart::slotAccounts()
{
    DiaAccounts dia(cfg,this);
    dia.exec();
    model.resetData(this->cfg->getLogins());
    this->ui->cb_server->setCurrentIndex(0);
}
