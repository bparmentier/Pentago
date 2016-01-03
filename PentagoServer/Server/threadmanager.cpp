#include "threadmanager.h"
#include <QtNetwork>
#include <vector>
ThreadManager::ThreadManager(qintptr ID, qintptr ID2, QObject *parent) :
    QThread(parent), game(nullptr),firstClientReady{false},secondClientReady{false},nextAction{Message::GameAction::PLACE_BALL}
{
    qDebug() << "new thread created";

    std::vector<Player> players;

    /* First client */
    firstClientSocket = new QTcpSocket();
    if(!firstClientSocket->setSocketDescriptor(ID)) {
        emit error(firstClientSocket->error());
        return;
    }
    connect(firstClientSocket, SIGNAL(readyRead()), this, SLOT(readyReadFirstClient()), Qt::DirectConnection);
    connect(firstClientSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    /* Second client */
    secondClientSocket = new QTcpSocket();
    if(!secondClientSocket->setSocketDescriptor(ID2)) {
        emit error(secondClientSocket->error());
        return;
    }
    connect(secondClientSocket, SIGNAL(readyRead()), this, SLOT(readyReadSecondClient()), Qt::DirectConnection);
    connect(secondClientSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    this->nextSocketPlayer = firstClientSocket;
    this->lengthMessage = 0;

    players.push_back(Player("player1", BallColor::BLACK, this->firstClientSocket));
    players.push_back(Player("player2", BallColor::WHITE, this->secondClientSocket));
    game = new Pentago(players);

    //Envoyer aux joueurs les parametres de la partie
    Message msg1(TypeMessage::READY);
    msg1.setPlayerColor(PlayerColor::BLACK);
    Message msg2(TypeMessage::READY);
    msg2.setPlayerColor(PlayerColor::WHITE);
    sendResponseOfServer(msg1,firstClientSocket);
    sendResponseOfServer(msg2,secondClientSocket);


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
    readFromSpecifiedSocket(firstClientSocket);
}

void ThreadManager::readyReadSecondClient()
{
    readFromSpecifiedSocket(secondClientSocket);
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
    processTheRequest(message,thisSocket);
    lengthMessage = 0;
}

void ThreadManager::processTheRequest(Message message,QTcpSocket * socket)
{
    switch (message.getType()){
    case TypeMessage::READY:
        if (socket == firstClientSocket)firstClientReady = true;
        if (socket == secondClientSocket)secondClientReady = true;
        if (firstClientReady && secondClientReady){
            sendPlaceBallRequest();
        }
        break;
    case TypeMessage::PLAY:
        qDebug() << "PLAY action received";
        game->play(message.getLine(),message.getColumn(), socket);
        qDebug()<< QString::fromStdString(game->getCurrentPlayerName()) << " played";
        sendRotateRequest();
        break;
    case TypeMessage::ROTATE:
        qDebug() << "ROTATE action received";
        game->rotate(message.getMiniBoardIndice(),message.isClockwiseRotation() == false ? Direction::CLOCKWISE : Direction::COUNTERCLOCKWISE, socket);
        sendPlaceBallRequest();
        break;
    }
}

void ThreadManager::disconnected() // probleme lors de la deconnexion d'un client, envoie à l'autre client qu'il a gagné par forfait puis le deconnecter? :/
{
    if(firstClientSocket != nullptr){
        firstClientSocket->deleteLater();
        firstClientSocket = nullptr;
    }
    if(secondClientSocket != nullptr){
        secondClientSocket->deleteLater();
        secondClientSocket = nullptr;
    }
    if(game != nullptr){
        delete game;
        game = nullptr;
    }
    this->exit(0);
}

void ThreadManager::sendResponseOfServer(const Message & message)
{
    sendResponseOfServer(message, firstClientSocket);
    sendResponseOfServer(message, secondClientSocket);
}

void ThreadManager::sendResponseOfServer(const Message & message,QTcpSocket *socket)
{
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);

    out << (quint16) 0;
    out << message;
    out.device()->seek(0);
    out << (quint16) (packet.size() - sizeof(quint16));

    socket->write(packet);
}

void ThreadManager::sendBoardToClients(){

    std::vector<std::vector<Hole>> tmp {game->getBoard()};
    QVector<QVector<PlayerColor>> vec = Message::convertBoard(tmp);
    Message msg(TypeMessage::BOARD_UPDATE);
    msg.setBoard(vec);
    sendResponseOfServer(msg);

}

void ThreadManager::sendPlaceBallRequest()
{
    qDebug() << "Sending place ball request";
    std::vector<std::vector<Hole>> tmp {game->getBoard()};
    QVector<QVector<PlayerColor>> vec = Message::convertBoard(tmp);

    Message msg(TypeMessage::PLAYER_TURN);
    msg.setGameAction(Message::GameAction::PLACE_BALL);
    msg.setPlayerColor(ballToPlayerColor(game->getCurrentPLayerBallColor()));
    msg.setBoard(vec);
    sendResponseOfServer(msg);
}

void ThreadManager::sendRotateRequest()
{
    qDebug() << "Sending rotate request";
    std::vector<std::vector<Hole>> tmp {game->getBoard()};
    QVector<QVector<PlayerColor>> vec = Message::convertBoard(tmp);

    Message msg(TypeMessage::PLAYER_TURN);
    msg.setGameAction(Message::GameAction::ROTATE);
    msg.setPlayerColor(ballToPlayerColor(game->getCurrentPLayerBallColor()));
    msg.setBoard(vec);
    sendResponseOfServer(msg);
}

PlayerColor ThreadManager::ballToPlayerColor(BallColor ballColor)
{
    PlayerColor color;
    switch (ballColor) {
    case BallColor::BLACK:
        color = PlayerColor::BLACK;
        break;
    case BallColor::WHITE:
        color = PlayerColor::WHITE;
        break;
    case BallColor::NONE:
        color = PlayerColor::NONE;
        break;
    }
    return color;
}
