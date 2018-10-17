#include "diaaccounts.h"
#include "ui_diaaccounts.h"

DiaAccounts::DiaAccounts(Config *cfg, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiaAccounts)
{
    ui->setupUi(this);
    this->cfg = cfg;
    proxy.setSourceModel(&model);
    this->ui->tv->setModel(&proxy);

    connect(this->ui->btn_create,&QPushButton::clicked,this,&DiaAccounts::slotCreate);
    connect(this->ui->btn_edit,&QPushButton::clicked,this,&DiaAccounts::slotEdit);
    connect(this->ui->tv,&QListView::doubleClicked,this,&DiaAccounts::slotEdit);
    connect(this->ui->btn_delete,&QPushButton::clicked,this,&DiaAccounts::slotDelete);
    connect(this->ui->le_filter,&QLineEdit::textChanged,&this->proxy,&AccountProxyModel::setFilter);
    this->ui->tv->installEventFilter(this);

    // get accounts from config
    this->cfg->load();
    this->model.resetData(cfg->getLogins());
}

DiaAccounts::~DiaAccounts()
{
    delete ui;
}

bool DiaAccounts::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress and obj->objectName() == "tv"){
        QKeyEvent * kev = static_cast<QKeyEvent *>(event);
        if ( (kev->key() == Qt::Key_Enter ) || (kev->key() == Qt::Key_Return) ){
            slotEdit();
        }
    }
    return QObject::eventFilter(obj, event);
}

void DiaAccounts::slotCreate()
{
    // add a new accaunt
    DiaLoginData dia(this);
    if(dia.execNew() != QDialog::Accepted)
        return;
    // add it into model
    model.addItem(dia.getLoginData());
    this->cfg->setLogins(this->model.getItems());
    this->cfg->save();
}

void DiaAccounts::slotEdit()
{
    // edit existing accaunt
    QModelIndex index = proxy.mapToSource(ui->tv->currentIndex());
    if(!index.isValid())
        return;
    LoginItem item = model.getItem(index);
    DiaLoginData dia(this);
    if(dia.execEdit(item) != QDialog::Accepted)
        return;
    model.updateItem(index,dia.getLoginData());
    this->cfg->setLogins(this->model.getItems());
    this->cfg->save();
}

void DiaAccounts::slotDelete()
{
    QModelIndex index = proxy.mapToSource(ui->tv->currentIndex());
    if(!index.isValid())
        return;
    LoginItem item = model.getItem(index);
    if( !AQP::question(this, tr("Question"), tr("Are you sure to delete this accaunt \"%1\"?")
            .arg(item.name))) {
        return;
    }
    model.deleteItem(index);
    this->cfg->setLogins(this->model.getItems());
    this->cfg->save();
}
