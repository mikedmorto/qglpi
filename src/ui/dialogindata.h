#ifndef DIALOGINDATA_H
#define DIALOGINDATA_H

#include <QDialog>

namespace Ui {
class DiaLoginData;
}

class DiaLoginData : public QDialog
{
    Q_OBJECT

public:
    explicit DiaLoginData(QWidget *parent = nullptr);
    ~DiaLoginData();

private:
    Ui::DiaLoginData *ui;
};

#endif // DIALOGINDATA_H
