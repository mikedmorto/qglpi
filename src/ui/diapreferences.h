#ifndef DIAPREFERENCES_H
#define DIAPREFERENCES_H

#include <QDialog>

namespace Ui {
class DiaPreferences;
}

class DiaPreferences : public QDialog
{
    Q_OBJECT

public:
    explicit DiaPreferences(QWidget *parent = nullptr);
    ~DiaPreferences();

private:
    Ui::DiaPreferences *ui;
};

#endif // DIAPREFERENCES_H
