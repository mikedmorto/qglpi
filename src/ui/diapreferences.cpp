#include "diapreferences.h"
#include "ui_diapreferences.h"

DiaPreferences::DiaPreferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiaPreferences)
{
    ui->setupUi(this);
    connect(this->ui->btn_cancel,&QPushButton::clicked,this,&DiaPreferences::close);
    connect(this->ui->btn_accept,&QPushButton::clicked,this,&DiaPreferences::accept);
}

DiaPreferences::~DiaPreferences()
{
    delete ui;
}
