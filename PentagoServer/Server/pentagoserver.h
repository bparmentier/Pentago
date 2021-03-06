#ifndef PENTAGOSERVER_H
#define PENTAGOSERVER_H
#include "threadmanager.h"
#include <QTcpServer>

class ThreadManager;

/*!
 * \brief The PentagoServer class
 * This is the class that operates the TCP server for the game
 */
class PentagoServer : public QTcpServer
{
    Q_OBJECT
    QList<qintptr> descriptorList; /*!< Collection containing the two client socket descriptors */
public:
    /*!
     * \brief PentagoServer
     * \param parent parent object (for deleting purposes)
     */
    explicit PentagoServer(QObject *parent = 0);
    /*!
     * \brief startServer starts the server on the local host
     * \param port the port number on which the server will listen for incoming connections. If the port number is 0, the port 50885 will be chosen
     */
    void startServer(int port);
    /*!
     * \brief stopServer stops the server from listening for incoming connections
     */
    void stopServer();
    /*!
     * \brief deleteFinishedThread allow to delete finished thread for array save
     * \param thread the thread to delete
     */
    void deleteFinishedThread(ThreadManager * thread);

signals:

public slots:

protected:
    /*!
     * \brief incomingConnection This function is called by QTcpServer when a new connection is available.
     * Once the server has received two connections, a thread will be started with both sockets
     * \param socketDescriptor a socket descriptor
     */
    void incomingConnection(qintptr socketDescriptor);
private:
    std::vector<ThreadManager * >threads;
};

#endif // PENTAGOSERVER_H
