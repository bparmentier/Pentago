#include "threadmanager.h"
#include "pentagoserver.h"

PentagoServer::PentagoServer(QObject *parent) :
    QTcpServer(parent)
{
}

void PentagoServer::startServer(int port)
{
    if (port == 0) port = 50885;
    if(!this->listen(QHostAddress::Any, port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Server Started, listening to port " << port << "...";
    }
}

void PentagoServer::stopServer()
{
    if(isListening()){
        close();
        qDebug()<<"Server Stopped";
    }
}

// This function is called by QTcpServer when a new connection is available.
void PentagoServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << socketDescriptor << " Connecting...";
    this->descriptorList << socketDescriptor;
    if(descriptorList.size() == 2){
        ThreadManager * thread = new ThreadManager(descriptorList.at(0), descriptorList.at(1), this);

        this->descriptorList.clear();
        // connect signal/slot. Once a thread is not needed, it will be beleted later
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        thread->start();
    }
}
