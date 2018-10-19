#include "mwmain.h"
#include "ui_mwmain.h"

MWMain::MWMain(QWidget *parent) :
    BaseWin(parent),
    ui(new Ui::MWMain)
{
    ui->setupUi(this);
    statusBar()->addWidget(&infobar);

    connect(this->ui->actionAbout,&QAction::triggered,this,&MWMain::slotAbout);
    connect(this->ui->actionQuit,&QAction::triggered,this,&MWMain::slotQuit);
}

void MWMain::start(const LoginItem &login, Config *cfg)
{
    this->BaseWin::start(login,cfg);
}

void MWMain::slotQuit()
{
    QApplication::quit();
}

MWMain::~MWMain()
{
    delete ui;
}

