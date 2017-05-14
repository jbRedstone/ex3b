#pragma once

#include "Exception.hpp"

class InvalidParameter : public Exception
{
public:
    InvalidParameter();
};
