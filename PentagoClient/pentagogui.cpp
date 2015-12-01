#include "pentagogui.h"
#include "ui_pentagogui.h"

PentagoGui::PentagoGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PentagoGui)
{
    ui->setupUi(this);

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
}

PentagoGui::~PentagoGui()
{
    delete thisClient;
    delete ui;
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
    //traitement de la reponse recu par le server + mise à jour interface ?
}

void PentagoGui::onConnectClicked() // bouton du menu qui permet de lancer une partie et ainsi de se connecter au serveur?
{
    thisClient->abort();
    thisClient->connectToHost("127.0.0.1", 50885);
}


void PentagoGui::connected() // Ce slot est appelé lorsque la connexion au serveur a réussi
{
    // lorsqu'on a réussi à se connecter ! initialiser l'interface ?
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
            break;
        case QAbstractSocket::ConnectionRefusedError:
            qDebug() << "ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.";
            break;
        case QAbstractSocket::RemoteHostClosedError:
            qDebug() <<"ERREUR : le serveur a coupé la connexion.";
            break;
        default:
            qDebug() <<"ERREUR : " << thisClient->errorString();
    }
}
