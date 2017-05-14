#pragma once

#include "Exception.hpp"

class InvalidCommand : public Exception
{
public:
    InvalidCommand();
};
