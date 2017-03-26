#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    argc = 0; argv = NULL;
    int retVal;
    QApplication app(argc, argv);
    MainWindow mw(&app);
    mw.show();
    retVal = app.exec();
    return retVal;
}
