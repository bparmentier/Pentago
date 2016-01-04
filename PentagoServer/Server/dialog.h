#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "pentagoserver.h"

namespace Ui {
class Dialog;
}

/*!
 * \brief The Dialog class A dialog for configuring,launching and stopping a PentagoServer
 */
class Dialog : public QDialog
{
    Q_OBJECT

private:
    Ui::Dialog *ui;
    PentagoServer server; /*!< The TCP server that will be launched */

public:

    /*!
     * \brief Sets up the dialog window
     * \param parent
     */
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:

    /*!
     * \brief startServer starts the server
     */
    void startServer();

    /*!
     * \brief stopServer stops the server and closes any open sockets
     */
    void stopServer();
};

#endif // DIALOG_H
