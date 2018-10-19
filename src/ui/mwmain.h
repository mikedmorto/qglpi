#ifndef MWMAIN_H
#define MWMAIN_H

#include <QMainWindow>
#include "basewin.h"

namespace Ui {
class MWMain;
}

class MWMain : public BaseWin
{
    Q_OBJECT

    const QString me = QString("MWMain");
public:
    explicit MWMain(QWidget *parent = nullptr);
    ~MWMain();
//    using BaseWin::start;
    void start(const LoginItem &login,Config * cfg) override;

private:
    Ui::MWMain *ui;
private slots:
    void slotQuit();
};

#endif // MWMAIN_H
