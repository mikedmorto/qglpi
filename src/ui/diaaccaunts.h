#ifndef DIAACCAUNTS_H
#define DIAACCAUNTS_H

#include <QDialog>
#include "dialogindata.h"

namespace Ui {
class DiaAccaunts;
}

class DiaAccaunts : public QDialog
{
    Q_OBJECT

public:
    explicit DiaAccaunts(QWidget *parent = nullptr);
    ~DiaAccaunts();

private:
    Ui::DiaAccaunts *ui;
};

#endif // DIAACCAUNTS_H
