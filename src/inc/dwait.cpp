#include "dwait.h"
#include "ui_dwait.h"

DWait::DWait(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DWait)
{
    ui->setupUi(this);
    isStoped = false;

    connect(ui->btn_cancel,&QPushButton::clicked,this,&DWait::slotCancel);
}

DWait::~DWait()
{
    delete ui;
}

void DWait::start(const QString &text, bool progress)
{
    isStoped = false;
    ui->label->setText(text);
    ui->progress->setVisible(progress);
//#ifdef Q_OS_WIN
//    QPoint dialogCenter = this->mapToGlobal(rect().center());
//    QPoint parentWindowCenter = this->parentWidget()->window()->mapToGlobal(
//                this->parentWidget()->window()->rect().center()
//                );
//    qDebug()<<"=================================";
//    qDebug()<<"diacenter - "<<dialogCenter;
//    qDebug()<<"parent center - "<<parentWindowCenter;
//    qDebug()<<"+++++++++++++++++++++++++++++++++";
//    move(parentWindowCenter - dialogCenter);
//#endif
    this->show();
}

void DWait::stop()
{
    isStoped = true;
    this->close();
}

bool DWait::tryStopState()
{
    return this->isStoped;
}

void DWait::closeEvent(QCloseEvent *event)
{
    if(isStoped){
        event->accept();
    }else{
        this->slotCancel();
        event->ignore();
    }
}

void DWait::keyPressEvent(QKeyEvent *e)
{
    // перехватываем esc клавишу закрытия диалога.
    if (e->key() == Qt::Key_Escape){
        this->slotCancel();
    }else{
        QDialog::keyPressEvent(e);
    }
}

void DWait::slotCancel()
{
    this->sigCancel();
    this->stop();
}

void DWait::setProgress(qint64 currentstatus, qint64 maxstatus)
{
    ui->progress->setMaximum(maxstatus);
    ui->progress->setValue(currentstatus);
}
