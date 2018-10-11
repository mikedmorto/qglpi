#ifndef MWSTART_H
#define MWSTART_H

#include <QMainWindow>
#include "diaabout.h"
#include "diapreferences.h"
#include "diaaccaunts.h"

namespace Ui {
class MWStart;
}

class MWStart : public QMainWindow
{
    Q_OBJECT
    Config * cfg;
public:
    explicit MWStart(Config * cfg, QWidget *parent = nullptr);
    ~MWStart();

private:
    Ui::MWStart *ui;
signals:
    void sigQuit();
private slots:
    void slotQuit();
    void slotAbout();
    void slotPreferences();
    void slotConnect();
    void slotAccounts();
};

#endif // MWSTART_H
