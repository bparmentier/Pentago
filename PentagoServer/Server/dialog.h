#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "pentagoserver.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    PentagoServer server;
private slots:
    void startServer();
    void stopServer();
};

#endif // DIALOG_H
