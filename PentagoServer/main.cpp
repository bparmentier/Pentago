#include <QApplication>
#include "Server/pentagoserver.h"
#include "Server/dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*PentagoServer server;
    server.startServer();

    return a.exec();*/
    Dialog e;
    return e.exec();
}
