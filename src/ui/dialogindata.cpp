#include "dialogindata.h"
#include "ui_dialogindata.h"

DiaLoginData::DiaLoginData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiaLoginData)
{
    ui->setupUi(this);
}

DiaLoginData::~DiaLoginData()
{
    delete ui;
}
