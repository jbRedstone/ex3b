#pragma once

#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>

using std::string;
using std::vector;
using std::cout;

class NTGate
{
public:
    NTGate();
    virtual bool getLogic(vector<bool> b);
    virtual string getName();
    virtual int getPars() const;
};
