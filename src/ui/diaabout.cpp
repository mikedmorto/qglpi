#include "diaabout.h"
#include "ui_diaabout.h"

DiaAbout::DiaAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiaAbout)
{
    ui->setupUi(this);

    QPixmap pix("://files/appicon.png");
    ui->lbl_icon->setPixmap(pix.scaled(128,128,Qt::KeepAspectRatio,Qt::SmoothTransformation));

    QString text;
    text.append(tr("<B>%1</B><BR><HR>").arg(APP_NAME));
    text.append(tr("Application version: %1").arg(GIT_VERSION));
    text.append("<BR>");
    text.append(tr("Build timestamp: %1 %2").arg(QString(__DATE__)).arg(QString(__TIME__)));
    text.append("<BR>");
    text.append(tr("Qt version: %1").arg(qVersion()));
    text.append("<BR>");
    text.append(tr("Operation system: %1, %2").arg(QSysInfo::productType()+" "+QSysInfo::productVersion()).arg(QSysInfo::currentCpuArchitecture()));
    this->ui->lbl_info->setText(text);

}

DiaAbout::~DiaAbout()
{
    delete ui;
}
