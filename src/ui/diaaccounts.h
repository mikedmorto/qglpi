#ifndef DiaAccounts_H
#define DiaAccounts_H

#include <QDialog>
#include <QEvent>
#include <QKeyEvent>
#include "dialogindata.h"
#include "config.h"
#include "aqp.hpp"

namespace Ui {
class DiaAccounts;
}

class DiaAccounts : public QDialog
{
    Q_OBJECT
    Config * cfg;
    AccountModel model;
    AccountProxyModel proxy;
public:
    explicit DiaAccounts(Config * cfg,QWidget *parent = nullptr);
    ~DiaAccounts();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
private:
    Ui::DiaAccounts *ui;
private slots:
    void slotCreate();
    void slotEdit();
    void slotDelete();
};

#endif // DiaAccounts_H
