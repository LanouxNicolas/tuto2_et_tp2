#include "rvwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RVWidget w;
    w.setWindowTitle("Réalité Virtuelle: Tuto2");
    w.show();
    return a.exec();
}
