#include "Exception.hpp"

Exception::Exception()
{}

Exception::Exception(string message) : m_errorMessage(message)
{}

string Exception::getMessage() const
{
    return m_errorMessage;
}

std::ostream & operator << (std::ostream & ostr, const Exception & exception)
{
    ostr << exception.getMessage();
    return ostr;
}
