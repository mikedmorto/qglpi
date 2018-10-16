#ifndef DIALOGINDATA_H
#define DIALOGINDATA_H

#include <QDialog>
#include "accountproxymodel.h"

namespace Ui {
class DiaLoginData;
}

class DiaLoginData : public QDialog
{
    Q_OBJECT

public:
    explicit DiaLoginData(QWidget *parent = nullptr);
    ~DiaLoginData();

    int execNew();
    int execEdit(const LoginItem &item);

    LoginItem getLoginData();

private:
    Ui::DiaLoginData *ui;
private slots:
    void slotValidate();
    void slotCheckedPass();
};

#endif // DIALOGINDATA_H
