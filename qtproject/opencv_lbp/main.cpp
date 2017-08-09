#include "mainwindow.h"
#include <QApplication>


int test_lbp();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();


    test_lbp();

    return a.exec();
}
