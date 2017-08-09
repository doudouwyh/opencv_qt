#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
    //w.showFullScreen();
    //w.setWindowFlags(Qt::WindowStaysOnTopHint);
    w.showMaximized();

    return a.exec();
}
