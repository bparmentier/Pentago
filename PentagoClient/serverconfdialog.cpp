#include "serverconfdialog.h"
#include "ui_serverconfdialog.h"

ServerConfDialog::ServerConfDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerConfDialog)
{
    ui->setupUi(this);
}

ServerConfDialog::~ServerConfDialog()
{
    delete ui;
}

QString ServerConfDialog::getServerAdress()
{
    return ui->serverAdress->text();
}

QString ServerConfDialog::getServerPort()
{
    return ui->serverPort->text();
}
