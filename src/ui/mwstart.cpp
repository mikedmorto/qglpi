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

    connect(this->ui->btn_quit,&QPushButton::clicked,this,&MWStart::slotQuit);
    connect(this->ui->btn_about,&QPushButton::clicked,this,&MWStart::slotAbout);
    connect(this->ui->btn_preferences,&QPushButton::clicked,this,&MWStart::slotPreferences);
    connect(this->ui->btn_connect,&QPushButton::clicked,this,&MWStart::slotConnect);
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
    dia.exec();

}
