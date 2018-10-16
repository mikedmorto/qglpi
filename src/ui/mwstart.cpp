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
    connect(this->dw,&DWait::sigCancel,&provider,&DataProvider::slotCancel);
    connect(&this->provider,&DataProvider::log,this,&MWStart::log);
    connect(this->ui->btn_quit,&QPushButton::clicked,this,&MWStart::slotQuit);
    connect(this->ui->btn_about,&QPushButton::clicked,this,&MWStart::slotAbout);
    connect(this->ui->btn_preferences,&QPushButton::clicked,this,&MWStart::slotPreferences);
    connect(this->ui->btn_connect,&QPushButton::clicked,this,&MWStart::slotConnect);
    connect(this->ui->btn_accaunts,&QPushButton::clicked,this,&MWStart::slotAccounts);
}

MWStart::~MWStart()
{
    delete ui;
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
    // save config

}

void MWStart::slotConnect()
{
    DiaLoginData dia(this);
    if(dia.execNew() != QDialog::Accepted)
        return;

    // try auth
    LoginItem item = dia.getLoginData();
    log(me,MLog::logDebug,tr("Try auth"));
    dw->start(tr("Connecting to \"%1\"").arg(item.name));
    if( !provider.auth(item) or dw->tryStopState() ){
        QString msg = tr("Error: %1").arg(provider.getLastError());
        log(me, MLog::logAlert, QString("Failure auth. %1").arg(msg));
        dw->stop();
        AQP::critical(this, "Error", msg);
        return;
    }
    log(me, MLog::logInfo, QString("success auth"));
    dw->stop();
    // auth done, test session_token

    QString result = provider.getResult();
    QJsonObject object = QJsonDocument::fromJson(result.toUtf8()).object();
    QString stok = object["session_token"].toString();


    if (stok.isEmpty()){
        QString msg = tr("Error: Session token is empty");
        AQP::critical(this, "Error", msg);
    }else{
        AQP::information(this, "Info", tr("Session token is %1").arg(stok));
    }
}

void MWStart::slotAccounts()
{
    DiaAccaunts dia(this);
    dia.exec();

}
