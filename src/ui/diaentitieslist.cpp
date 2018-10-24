#include "diaentitieslist.h"
#include "ui_diaentitieslist.h"

DiaEntitiesList::DiaEntitiesList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiaEntitiesList)
{
    ui->setupUi(this);
}

DiaEntitiesList::~DiaEntitiesList()
{
    delete ui;
}
