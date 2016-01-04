#ifndef PENTAGOSERVER_H
#define PENTAGOSERVER_H

#include <QTcpServer>

class PentagoServer : public QTcpServer
{
    Q_OBJECT
    QList<qintptr> descriptorList;
public:
    explicit PentagoServer(QObject *parent = 0);
    void startServer(int port);
    void stopServer();

signals:

public slots:

protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif // PENTAGOSERVER_H
