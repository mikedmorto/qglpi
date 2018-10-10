#ifndef DIAPREFERENCES_H
#define DIAPREFERENCES_H

#include <QDialog>
#include "def.h"
#include "config.h"

namespace Ui {
class DiaPreferences;
}

class DiaPreferences : public QDialog
{
    Q_OBJECT

    Config * cfg;
public:
    explicit DiaPreferences(Config * cfg, QWidget *parent = nullptr);
    ~DiaPreferences();

private:
    Ui::DiaPreferences *ui;
private slots:
    void slotPreAccept();
};

#endif // DIAPREFERENCES_H
