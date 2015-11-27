#include "pentagoexception.h"

PentagoException::PentagoException(std::string message)throw()
{
    m_message = message;
}

const char* PentagoException::what() const throw(){
    return m_message.c_str();
}

PentagoException::~PentagoException() throw(){

}

