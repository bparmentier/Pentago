#include "dialog.h"
#include "ui_dialog.h"
#include "Server/pentagoserver.h"
#include "Server/dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->stopButton->setDisabled(true);
    ui->portText->setText("50885");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::startServer()
{
    server.startServer(ui->portText->text().toInt());
    ui->startButton->setDisabled(true);
    ui->stopButton->setDisabled(false);
}

void Dialog::stopServer()
{
    //will stop server here
    server.stopServer();
    ui->startButton->setDisabled(false);
    ui->stopButton->setDisabled(true);
}
