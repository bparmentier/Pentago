#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include "business/pentago.h"
#include "message.h"
#include "type.h"
#include "pentagoserver.h"

class PentagoServer;

/*!
 * \brief The ThreadManager class Manages a Pentago server thread and processes client requests
 */
class ThreadManager : public QThread
{
    Q_OBJECT
private:
    QTcpSocket * firstClientSocket;     /*!<  this first socket */
    QTcpSocket * secondClientSocket;    /*!<  the second socket */
    bool firstClientReady;              /*!<  Indicated if the first client is ready to play */
    bool secondClientReady;             /*!<  Indicated if the second client is ready to play */
    Pentago * game;                     /*!<  a Pentago game instance */
    quint16 lengthMessage;              /*!<  used to store the size of a packet to be sent on the network */
    PentagoServer * parent;             /*!<  used when need to delete finished thread from array in server */
public:

    /*!
     * \brief ThreadManager Constructs a new ThreadManager to manage a new thread containing two Sockets (client).
     * \param ID a connection descriptor identifier
     * \param ID2 a connection descriptor identifier
     * \param parent parent Object
     */
    explicit ThreadManager(qintptr ID, qintptr ID2, QObject *parent = 0);

    /*!
     * \brief run The starting point for the thread. After calling start(), the newly created thread calls this function.
     */
    void run();

    /*!
     * \brief closeConnections
     */
    void closeConnections();

signals:

    /*!
     * \brief error signal that is generated when an error occurs on a socket
     * \param socketerror the socket that generated the error
     */
    void error(QTcpSocket::SocketError socketerror);

public slots:

    /*!
     * \brief readyReadFirstClient Slot is called when a packet from the first client is ready to be read
     */
    void readyReadFirstClient();

    /*!
     * \brief readyReadSecondClient Slot is called when a packet from the second client is ready to be read
     */
    void readyReadSecondClient();

    /*!
     * \brief disconnected Slot that is called when a socket has closed unexpectedly
     */
    void disconnected();

private:
    void readFromSpecifiedSocket(QTcpSocket * thisSocket);
    void processTheRequest(Message message,QTcpSocket * socket);
    void sendResponseOfServer(const Message &message);
    void sendResponseOfServer(const Message &message, QTcpSocket *socket);
    void sendPlaceBallRequest();
    void sendRotateRequest();
    void sendError(const QString &message, QTcpSocket *socket);
    void sendEndGameMessage();

    static PlayerColor ballToPlayerColor(BallColor ballColor);
};

#endif // CLIENTTHREAD_H
