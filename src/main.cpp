#include <QApplication>
#include <QCommandLineParser>
#include "def.h"
#include "mwstart.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MWStart ws;
    ws.show();

    return a.exec();
}
