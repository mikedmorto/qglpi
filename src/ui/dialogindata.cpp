#include "dialogindata.h"
#include "ui_dialogindata.h"
#include <QDebug>

DiaLoginData::DiaLoginData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiaLoginData)
{
    ui->setupUi(this);
    connect(this->ui->le_accname,&QLineEdit::textChanged,this,&DiaLoginData::slotValidate);
    connect(this->ui->le_serverurl,&QLineEdit::textChanged,this,&DiaLoginData::slotValidate);
    connect(this->ui->le_apptoken,&QLineEdit::textChanged,this,&DiaLoginData::slotValidate);
    connect(this->ui->tabw,&QTabWidget::currentChanged,this,&DiaLoginData::slotValidate);
    connect(this->ui->le_login,&QLineEdit::textChanged,this,&DiaLoginData::slotValidate);
    connect(this->ui->le_pass,&QLineEdit::textChanged,this,&DiaLoginData::slotValidate);
    connect(this->ui->le_token,&QLineEdit::textChanged,this,&DiaLoginData::slotValidate);
    connect(this->ui->chbox_showpass,&QCheckBox::released,this,&DiaLoginData::slotCheckedPass);

}

DiaLoginData::~DiaLoginData()
{
    delete ui;
}

int DiaLoginData::execNew()
{
    this->ui->btn_accept->setEnabled(false);
    return this->exec();
}

int DiaLoginData::execEdit(const LoginItem &item)
{
    this->ui->tabw->setCurrentIndex(item.authType);
    this->ui->le_accname->setText(item.name);
    this->ui->le_serverurl->setText(item.serverurl);
    this->ui->le_apptoken->setText(item.apptoken);
    this->ui->le_login->setText(item.login);
    this->ui->le_pass->setText(item.pass);
    this->ui->le_token->setText(item.token);

    return this->exec();
}

LoginItem DiaLoginData::getLoginData()
{
    LoginItem item;
    item.authType = this->ui->tabw->currentIndex();
    item.name = this->ui->le_accname->text();
    item.serverurl = this->ui->le_serverurl->text();
    item.apptoken = this->ui->le_apptoken->text();
    item.login = this->ui->le_login->text();
    item.pass = this->ui->le_pass->text();
    item.token = this->ui->le_token->text();

    return item;
}

void DiaLoginData::slotValidate()
{
    bool isok = true;
    if(this->ui->le_accname->text().isEmpty())
        isok = false;
    if(this->ui->le_serverurl->text().isEmpty())
        isok = false;
    if(this->ui->le_apptoken->text().isEmpty())
        isok = false;
    switch (this->ui->tabw->currentIndex()) {
    case 0: // login pass
    default:
    {
        if(this->ui->le_login->text().isEmpty())
                isok = false;
        if(this->ui->le_pass->text().isEmpty())
                isok = false;
    }
        break;
    case 1: // token
    {
        if(this->ui->le_token->text().isEmpty())
                isok = false;
    }
        break;
    }

    this->ui->btn_accept->setEnabled(isok);
}

void DiaLoginData::slotCheckedPass()
{
    if(this->ui->chbox_showpass->isChecked()){
        this->ui->le_pass->setEchoMode(QLineEdit::Normal);
        return;
    }

    this->ui->le_pass->setEchoMode(QLineEdit::Password);
}
