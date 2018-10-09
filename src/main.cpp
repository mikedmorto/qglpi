#include <QApplication>
#include <QCommandLineParser>
#include "def.h"
#include "wctrl.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Wctrl w;
    QObject::connect(&a,&QApplication::aboutToQuit,&w,&Wctrl::slotQuit);
    w.start();
    return a.exec();
}
