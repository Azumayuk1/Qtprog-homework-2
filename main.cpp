#include "mainwindow.h"
//#include "Mygraphics.h"
//#include "mydiagram.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //MyDiagram d;
    //d.show();


    return a.exec();
}
