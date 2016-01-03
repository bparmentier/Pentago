#include "serverconfdialog.h"
#include "ui_serverconfdialog.h"

ServerConfDialog::ServerConfDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerConfDialog)
{
    ui->setupUi(this);
    ui->serverAdress->setText("127.0.0.1");
    ui->serverPort->setText("50885");
}

ServerConfDialog::~ServerConfDialog()
{
    delete ui;
}

QString ServerConfDialog::getServerAdress() const
{
    return ui->serverAdress->text();
}

QString ServerConfDialog::getServerPort()const
{
    return ui->serverPort->text();
}
