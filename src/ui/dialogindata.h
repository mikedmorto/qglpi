#ifndef DIALOGINDATA_H
#define DIALOGINDATA_H

#include <QDialog>

namespace Ui {
class DiaLoginData;
}

struct LoginItem{
    enum AuthType{
        Password = 0,
        Token = 1
    };
    int authType = Password;
    QString name;
    QString serverurl;
    QString apptoken;
    QString login;
    QString pass;
    QString token;
};


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
