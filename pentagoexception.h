/*!
 * \file pentagoexception.h
 * \brief Définition de la classe PentagoException.
 */

#ifndef PENTAGOEXCEPTION_H
#define PENTAGOEXCEPTION_H

#include <exception>
#include <string>

/*!
 * \brief Classe représentant l'exception lancée par le jeu Pentago
 */
class PentagoException : public std::exception
{

private:

    std::string m_message;

public:

    /*!
     * \brief   Constructeur de la classe avec paramètre
     * \param   message     le message d'info sur l'erreur survenue
     */
    PentagoException(std::string message)throw();

    /*!
     * \brief   Méthode de la classe permettant de renvoyer le message d'erreur
     * \return  Le message d'erreur
     */
    virtual const char* what() const throw();

    /*!
     * \brief   Destructeur de la classe
     */
    virtual ~PentagoException() throw();

};

#endif // PENTAGOEXCEPTION_H
