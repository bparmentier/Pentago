#include "threadmanager.h"
#include "pentagoserver.h"

PentagoServer::PentagoServer(QObject *parent) :
    QTcpServer(parent)
{
}

void PentagoServer::startServer()
{
    int port = 50885;
    if(!this->listen(QHostAddress::Any, port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Server Started, listening to port " << port << "...";
    }
}

// This function is called by QTcpServer when a new connection is available.
void PentagoServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << socketDescriptor << " Connecting...";
    this->DescriptorList << socketDescriptor;
    if(DescriptorList.size() == 2){
        ThreadManager * thread = new ThreadManager(DescriptorList.at(0),DescriptorList.at(1), this);
        this->DescriptorList.clear();
        // connect signal/slot. Once a thread is not needed, it will be beleted later
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        thread->start();
    }
}
