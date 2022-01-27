#include "rvwidget.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //RVWidget w;
    MainWindow w;
    w.setWindowTitle("Réalité Virtuelle: Tp2 Nicolas LANOUX");
    w.show();
    return a.exec();
}
