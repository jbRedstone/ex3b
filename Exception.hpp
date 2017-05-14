#pragma once

#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>

using std::string;
using std::vector;
using std::cout;
using std::endl;

class Exception
{
public:
    Exception();
    Exception(string message);
    string getMessage() const;
protected:
    string m_errorMessage;
};

std::ostream & operator << (std::ostream & ostr, const Exception & exception);
