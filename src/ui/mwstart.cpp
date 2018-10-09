#include "mwstart.h"
#include "ui_mwstart.h"

MWStart::MWStart(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MWStart)
{
    ui->setupUi(this);
    this->ui->statusbar->setHidden(true);
    QPixmap pix("://files/appicon.png");
    ui->lbl_icon->setPixmap(pix.scaled(128,128,Qt::KeepAspectRatio,Qt::SmoothTransformation));

    connect(this->ui->btn_quit,&QPushButton::clicked,this,&MWStart::slotQuit);
    connect(this->ui->btn_about,&QPushButton::clicked,this,&MWStart::slotAbout);
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
