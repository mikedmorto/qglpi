#include "mwstart.h"
#include "ui_mwstart.h"

MWStart::MWStart(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MWStart)
{
    ui->setupUi(this);
    this->ui->statusbar->setHidden(true);
}

MWStart::~MWStart()
{
    delete ui;
}
