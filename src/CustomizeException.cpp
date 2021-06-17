#include "CustomizeException.h"

CustomizeException::CustomizeException(const string &message) throw()
{
    this->userMessage = message;
}

CustomizeException::~CustomizeException() throw()
{
}

const char *CustomizeException::what() const throw()
{
    return userMessage.c_str();
}