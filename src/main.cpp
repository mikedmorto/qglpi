#include <QApplication>
#include <QCommandLineParser>
#include "def.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<" I am a test";
    exit(0);
    return a.exec();
}
