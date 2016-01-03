#ifndef SERVERCONFDIALOG_H
#define SERVERCONFDIALOG_H

#include <QDialog>

namespace Ui {
class ServerConfDialog;
}

class ServerConfDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerConfDialog(QWidget *parent = 0);
    ~ServerConfDialog();
    QString getServerAdress()const;
    QString getServerPort()const;

private:
    Ui::ServerConfDialog *ui;
};

#endif // SERVERCONFDIALOG_H
