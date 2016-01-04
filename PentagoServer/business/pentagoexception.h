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
     * \brief   constructor of PentagoException
     * \param   message     the message of the exception
     */
    PentagoException(std::string message)throw();

    /*!
     * \brief   allow to get the message of the exception
     * \return  the message
     */
    virtual const char* what() const throw();

    /*!
     * \brief   destructor of the class
     */
    virtual ~PentagoException() throw();

};

#endif // PENTAGOEXCEPTION_H
