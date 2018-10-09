#ifndef MWSTART_H
#define MWSTART_H

#include <QMainWindow>
#include "diaabout.h"

namespace Ui {
class MWStart;
}

class MWStart : public QMainWindow
{
    Q_OBJECT

public:
    explicit MWStart(QWidget *parent = nullptr);
    ~MWStart();

private:
    Ui::MWStart *ui;
signals:
    void sigQuit();
private slots:
    void slotQuit();
    void slotAbout();
};

#endif // MWSTART_H
