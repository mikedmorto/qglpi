#ifndef DIAABOUT_H
#define DIAABOUT_H

#include <QDialog>
#include <QDateTime>
#include "def.h"

namespace Ui {
class DiaAbout;
}

class DiaAbout : public QDialog
{
    Q_OBJECT

public:
    explicit DiaAbout(QWidget *parent = 0);
    ~DiaAbout();

private:
    Ui::DiaAbout *ui;
};

#endif // DIAABOUT_H
