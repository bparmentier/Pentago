#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include "business/pentago.h"
#include "message.h"
#include "type.h"

class ThreadManager : public QThread
{
    Q_OBJECT
private:
    QTcpSocket * firstClientSocket;
    QTcpSocket * secondClientSocket;
    bool firstClientReady;
    bool secondClientReady;
    QTcpSocket * nextSocketPlayer; // joueur duquel on attend le mouvement, si pas lui on refuse de jouer le mouvement demandé !
    Pentago * game;
    quint16 lengthMessage;
    Message::GameAction nextAction;

public:
    explicit ThreadManager(qintptr ID, qintptr ID2, QObject *parent = 0);
    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyReadFirstClient();
    void readyReadSecondClient();
    void disconnected();

private:
    void readFromSpecifiedSocket(QTcpSocket * thisSocket);
    void processTheRequest(Message message,QTcpSocket * socket);
    void sendResponseOfServer(const Message &message);
    void sendResponseOfServer(const Message &message, QTcpSocket *socket);
    void startPlay();
    void sendBoardToClients();
    void sendPlaceBallRequest();
    void sendRotateRequest();

    static PlayerColor ballToPlayerColor(BallColor ballColor);
};

#endif // CLIENTTHREAD_H
