#include "pentagogui.h"
#include "ui_pentagogui.h"
#include "qhole.h"
#include <QMessageBox>
#include "serverconfdialog.h"

PentagoGui::PentagoGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PentagoGui)
{
    ui->setupUi(this);
    ui->graphicsView->setHidden(true);
    thisClient = new QTcpSocket(this);
    connect(thisClient, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(thisClient, SIGNAL(connected()), this, SLOT(connected()));
    connect(thisClient, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(thisClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorSocket(QAbstractSocket::SocketError)));
    connect(ui->actionConnect, &QAction::triggered,
            this, &PentagoGui::onConnectClicked);
    connect(ui->actionQuit, &QAction::triggered,
            &QCoreApplication::quit);

    lengthMessage = 0;
    ui->graphicsView->setDisabled(true);
}

PentagoGui::~PentagoGui()
{
    delete thisClient;
    delete ui;
}

void PentagoGui::play(int line, int column)
{
    Message msg(TypeMessage::PLAY);
    msg.setLine(line);
    msg.setColumn(column);
    sendMessageToServer(msg);
}

void PentagoGui::rotate(int miniboard, bool clockwise)
{
    qDebug() << "miniboard: " << miniboard;
    qDebug() << "clockwise? " << clockwise;
    Message msg(TypeMessage::ROTATE);
    msg.setClockwiseRotation(clockwise);
    msg.setMiniBoardIndice(miniboard);
    sendMessageToServer(msg);
}

void PentagoGui::onPlayRequest()
{
    // traitement d'un placement de bille
}

void PentagoGui::onRotateRequest()
{
    // traitement d'une rotation d'un plateau
}

void PentagoGui::sendMessageToServer(Message messageToSend)
{
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);

    out << (quint16) 0;
    out << messageToSend;
    out.device()->seek(0);
    out << (quint16) (packet.size() - sizeof(quint16));

    thisClient->write(packet); // On envoie le paquet
}

void PentagoGui::processTheMessage(Message messageFromServer)
{
    switch (messageFromServer.getType()) {
    case TypeMessage::READY:
    {
        playerColor = messageFromServer.getPlayerColor();
        qDebug() << "Message reçu";
        if (playerColor == PlayerColor::BLACK){
            board->setColor(QBallColor::BLACK);
            setStatusTip("You play with the black balls");
            qDebug() << "BLACK";
        } else {
            board->setColor(QBallColor::WHITE);
            setStatusTip("You play with the white balls");
            qDebug() << "WHITE";
        }
        Message msg(TypeMessage::READY);
        sendMessageToServer(msg);
    }
        break;
    case TypeMessage::PLAYER_TURN:
    {
        qDebug() << "PLAYER_TURN received";
        QVector<QVector<PlayerColor>> vec = messageFromServer.getBoard();
        board->updateBoard(vec);

        if (messageFromServer.getGameAction() == Message::GameAction::PLACE_BALL) {
            qDebug() << "PLACE_BALL";
            if (messageFromServer.getPlayerColor() == playerColor) {
                qDebug() << "It's my turn";
                setStatusTip("Place your ball");
                ui->graphicsView->setDisabled(false);
            } else {
                qDebug() << "Other player's turn";
                setStatusTip("Waiting for the other player to place his ball");
                ui->graphicsView->setDisabled(true);
            }
        } else if (messageFromServer.getGameAction() == Message::GameAction::ROTATE) {
            qDebug() << "ROTATE";
            if (messageFromServer.getPlayerColor() == playerColor) {
                qDebug() << "It's my turn";
                setStatusTip("Rotate a mini-board");
                board->readyrotate();
            } else {
                qDebug() << "Other player's turn";
                setStatusTip("Waiting for the other player to rotate his mini-board");
            }
        }
    }
        break;
    case TypeMessage::FINISHED:
    {
        QVector<QVector<PlayerColor>> vec = messageFromServer.getBoard();
        board->updateBoard(vec);

        QString endMessage;
        QString endTitle;
        if (messageFromServer.getPlayerColor() == playerColor) {
            endTitle = "Congratulations!";
            endMessage = "You won!";
        } else if (messageFromServer.getPlayerColor() == PlayerColor::NONE) {
            endTitle = "Draw game";
            endMessage = "Nobody won!";
        } else {
            endTitle = "Too bad!";
            endMessage = "You lost!";
        }
        QMessageBox::information(this, endTitle, endMessage);
        ui->graphicsView->setDisabled(true);
        showStatusTip("");
    }
        break;
    case TypeMessage::ERROR:
    {
        QMessageBox::information(this, "Erreur",
                                 messageFromServer.getError());
    }
        break;
    }
}

void PentagoGui::showStatusTip(const QString &message)
{
    statusBar()->showMessage(message);
}

void PentagoGui::onConnectClicked() // bouton du menu qui permet de lancer une partie et ainsi de se connecter au serveur?
{
    ServerConfDialog cd{this};
    auto ret= cd.exec();
    if(ret && !cd.getServerAdress().isEmpty() && !cd.getServerPort().isEmpty() && cd.getServerPort().toUInt() != 0){
        thisClient->abort();
        thisClient->connectToHost(cd.getServerAdress(),cd.getServerPort().toUInt());
    }else if (ret){
        QMessageBox::information(this,"Incorrect Parameters ","The parameters you entered are incorrect :\nPlease check the IP address and port number");
    }
}

void PentagoGui::connected() // Ce slot est appelé lorsque la connexion au serveur a réussi
{
    // lorsqu'on a réussi à se connecter ! initialiser l'interface ?
    board = new QBoard(this);
    ui->graphicsView->setHidden(false);
    ui->graphicsView->setScene(board);

}

void PentagoGui::readyRead()
{
    QDataStream in(thisClient);
    if (lengthMessage == 0)
    {
        if (thisClient->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> lengthMessage;
    }
    if (thisClient->bytesAvailable() < lengthMessage)
        return;
    Message messageFromServer;
    in >> messageFromServer;
    processTheMessage(messageFromServer);
    lengthMessage = 0;
}

// Ce slot est appelé lorsqu'on est déconnecté du serveur
void PentagoGui::disconnected()
{
    // ce qu'il faut faire quand le server nous deconnecte. Normalement en fin de partie
}


void PentagoGui::errorSocket(QAbstractSocket::SocketError error) // Ce slot est appelé lorsqu'il y a une erreur
{
    switch(error)
    {
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.";
        QMessageBox::information(this,"Error Connecting to server","Server was not found.\n Please check ip adress and port.");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.";
        QMessageBox::information(this,"Error Connecting to server","Server was not found.\n Please check if server is running and check ip adress and port.");
        break;
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() <<"ERREUR : le serveur a coupé la connexion.";
        QMessageBox::information(this,"Server ended connection","The server ended the connection");
        break;
    default:
        qDebug() <<"ERREUR : " << thisClient->errorString();
    }
}
