#include "mainwindow.h"
#include <QApplication>

int ml_test();
int dt_mashroom();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();

    //ml_test();
    dt_mashroom();

    return a.exec();
}
