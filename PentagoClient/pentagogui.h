#ifndef PENTAGOGUI_H
#define PENTAGOGUI_H

#include <QMainWindow>
#include <QtNetwork>
#include "message.h"
#include "qboard.h"

namespace Ui {
class PentagoGui;
}

class PentagoGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit PentagoGui(QWidget *parent = 0);
    ~PentagoGui();

private:
    Ui::PentagoGui * ui;
    QTcpSocket * thisClient;
    quint16 lengthMessage;
    QBoard *board;

private slots:
    void onPlayRequest();
    void onRotateRequest();

    void onConnectClicked();
    void connected();
    void readyRead();
    void disconnected();
    void errorSocket(QAbstractSocket::SocketError error);

private:
    void sendMessageToServer(Message messageToSend);
    void processTheMessage(Message messageFromServer);

};

#endif // PENTAGOGUI_H
