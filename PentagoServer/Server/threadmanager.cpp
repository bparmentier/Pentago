#include "threadmanager.h"
#include <QtNetwork>
#include <vector>

using namespace std;

ThreadManager::ThreadManager(qintptr ID, qintptr ID2, QObject *parent) :
    QThread(parent), game(nullptr)
{
    vector<Player> players;
    players.push_back(Player("player1",BallColor::BLACK));
    players.push_back(Player("player2",BallColor::WHITE));
    game = new Pentago(players);

    firstSocket = new QTcpSocket();
    if(!firstSocket->setSocketDescriptor(ID))
    {
        // something's wrong, we just emit a signal
        emit error(firstSocket->error());
        return;
    }
    connect(firstSocket, SIGNAL(readyRead()), this, SLOT(readyReadFirstClient()), Qt::DirectConnection);
    connect(firstSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    secondClient = new QTcpSocket();
    if(!secondClient->setSocketDescriptor(ID2))
    {
        emit error(secondClient->error());
        return;
    }
    connect(secondClient, SIGNAL(readyRead()), this, SLOT(readyReadSecondClient()), Qt::DirectConnection);
    connect(secondClient, SIGNAL(disconnected()), this, SLOT(disconnected()));

    this->nextSocketPlayer = firstSocket;
    this->lengthMessage = 0;
}

void ThreadManager::run()
{
    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies
    exec();
}

void ThreadManager::readyReadFirstClient()
{
    readFromSpecifiedSocket(firstSocket);
}

void ThreadManager::readyReadSecondClient()
{
    readFromSpecifiedSocket(secondClient);
}

void ThreadManager::readFromSpecifiedSocket(QTcpSocket * thisSocket)
{
    QDataStream in(thisSocket);
    if (lengthMessage == 0)
    {
        if (thisSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> lengthMessage;
    }
    if (thisSocket->bytesAvailable() < lengthMessage)
        return;
    Message message;
    in >> message;
    processTheRequest(message);
    lengthMessage = 0;
}

void ThreadManager::processTheRequest(Message message)
{
    Message serverResponse;
    switch(message.getType()){
    case TypeMessage::PLAY:
        // action on play request
        break;
    case TypeMessage::ROTATE:
        // action on rotate request
        break;
    }
    sendResponseOfServer(serverResponse); // mise à jour de l'interface du client
    if(game->isFinished()){
        serverResponse = Message();
        sendResponseOfServer(serverResponse); // envoie de l'etat final du jeu ?
    }
}

void ThreadManager::disconnected() // probleme lors de la deconnexion d'un client, envoie à l'autre client qu'il a gagné par forfait puis le deconnecter? :/
{
    if(firstSocket != nullptr){
        firstSocket->deleteLater();
        firstSocket = nullptr;
    }
    if(secondClient != nullptr){
        secondClient->deleteLater();
        secondClient = nullptr;
    }
    if(game != nullptr){
        delete game;
        game = nullptr;
    }
    this->exit(0);
}

void ThreadManager::sendResponseOfServer(const Message & message)
{
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);

    out << (quint16) 0;
    out << message;
    out.device()->seek(0);
    out << (quint16) (packet.size() - sizeof(quint16));

    firstSocket->write(packet);
    secondClient->write(packet);
}
