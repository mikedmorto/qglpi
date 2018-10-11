#include "diaaccaunts.h"
#include "ui_diaaccaunts.h"

DiaAccaunts::DiaAccaunts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiaAccaunts)
{
    ui->setupUi(this);
}

DiaAccaunts::~DiaAccaunts()
{
    delete ui;
}
