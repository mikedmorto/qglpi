#ifndef MWSTART_H
#define MWSTART_H

#include <QMainWindow>
#include "diaabout.h"
#include "diapreferences.h"
#include "diaaccaunts.h"
#include "dwait.h"
#include "dataprovider.h"
#include "aqp.hpp"

namespace Ui {
class MWStart;
}

class MWStart : public QMainWindow
{
    Q_OBJECT
    Config * cfg;
    Ui::MWStart *ui;
    DWait * dw;
    DataProvider provider;
    QString me = "MWStart";
public:
    explicit MWStart(Config * cfg, QWidget *parent = nullptr);
    ~MWStart();

signals:
    void sigQuit();
    void log(const QString &,MLog::LogLevel,const QString &);
private slots:
    void slotQuit();
    void slotAbout();
    void slotPreferences();
    void slotConnect();
    void slotAccounts();
};

#endif // MWSTART_H
