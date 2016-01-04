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
    /*!
     * \brief Constructs a dialog asking for a server address and port
     * \param parent the parent widget
     */
    explicit ServerConfDialog(QWidget *parent = 0);

    ~ServerConfDialog();

    /*!
     * \brief Returns the entered server address
     * \return the entered server address
     */
    QString getServerAdress() const;

    /*!
     * \brief Returns the entered server port
     * \return the entered server port
     */
    QString getServerPort() const;

private:
    Ui::ServerConfDialog *ui;
};

#endif // SERVERCONFDIALOG_H
