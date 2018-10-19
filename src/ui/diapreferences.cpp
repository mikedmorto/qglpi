#include "diapreferences.h"
#include "ui_diapreferences.h"

DiaPreferences::DiaPreferences(Config *cfg, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiaPreferences)
{
    ui->setupUi(this);
    connect(this->ui->btn_cancel,&QPushButton::clicked,this,&DiaPreferences::close);
    connect(this->ui->btn_accept,&QPushButton::clicked,this,&DiaPreferences::slotPreAccept);


    // load configuration from configuration file
    this->cfg = cfg;
    this->ui->le_logpath->setText(this->cfg->getLogfile());
    this->ui->cbox_lang->setCurrentIndex(this->cfg->getLang());
    this->ui->cbox_loglevel->setCurrentIndex(this->cfg->getLoglevel());
    this->ui->cbox_ignoreSsl->setChecked(this->cfg->getIgnoreSsl());
}

DiaPreferences::~DiaPreferences()
{
    delete ui;
}

void DiaPreferences::slotPreAccept()
{
    // set config and save it
    this->cfg->setLang(this->ui->cbox_lang->currentIndex());
    this->cfg->setLogfile(this->ui->le_logpath->text());
    this->cfg->setLoglevel(this->ui->cbox_loglevel->currentIndex());
    this->cfg->setIgnoreSsl(this->ui->cbox_ignoreSsl->isChecked());
    this->cfg->save();
    this->accept();
}
