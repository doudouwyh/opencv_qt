#include "mainwindow.h"
#include <QApplication>


int lda_test();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();

    lda_test();

    return a.exec();
}
