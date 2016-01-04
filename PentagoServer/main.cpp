#include <QApplication>
#include "Server/pentagoserver.h"
#include "Server/dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog e;
    return e.exec();
}
