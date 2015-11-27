#include "pentagogui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PentagoGui w;
    w.show();

    return a.exec();
}
