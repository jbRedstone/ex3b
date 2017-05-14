#pragma once

#include "NTGate.hpp"

class CompositeGate : public NTGate
{
public:
    CompositeGate();
    CompositeGate(vector<NTGate*> g);
    bool getLogic(vector <bool> params);
    string getName();
    vector <NTGate*> getGates();
    int getPars() const;
private:
    vector <NTGate*> m_gates;
    int m_parNum;
    string m_name;
};

