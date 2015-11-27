#include <QApplication>
#include "Server/pentagoserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PentagoServer server;
    server.startServer();

    return a.exec();
}
