#ifndef PENTAGOGUI_H
#define PENTAGOGUI_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QtNetwork>
#include "message.h"
#include "qboard.h"
#include "playercolor.h"

class QBoard;

namespace Ui {
class PentagoGui;
}

class PentagoGui : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Constructs a Pentago window
     * \param parent the parent widget
     */
    explicit PentagoGui(QWidget *parent = 0);

    ~PentagoGui();

    /*!
     * \brief Sends a PLAY message to the server with the given coordinates
     * \param line the line
     * \param column the column
     */
    void play(int line, int column);

    /*!
     * \brief Sends a ROTATE message to the server with the given mini-board id
     * and rotation direction
     * \param miniboard the miniboard id
     * \param clockwise true if a clockwise rotation, false otherwise
     */
    void rotate(int miniboard, bool clockwise);

private:
    Ui::PentagoGui * ui;
    QTcpSocket * thisClient;
    quint16 lengthMessage;
    QBoard *board;
    PlayerColor playerColor;

private slots:
    void onConnectClicked();
    void onCloseClicked();
    void connected();
    void readyRead();
    void disconnected();
    void errorSocket(QAbstractSocket::SocketError error);

private:
    void sendMessageToServer(Message messageToSend);
    void processTheMessage(Message messageFromServer);
    void sendBeginStateToServer(PlayerColor color);
    void showStatusTip(const QString &message);
};

#endif // PENTAGOGUI_H
