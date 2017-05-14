#pragma once

#include "NTGate.hpp"

const bool F = 0, T = 1;

template <class U>
class Gate : public NTGate

{
public:
    Gate();
    Gate(U tTable, int parNum = 0, string name = "");
    bool getLogic(vector<bool> b);
    bool getLogic(vector<bool> b, U tTable);
    virtual string getName();
    int getPars() const;

protected:
    int m_parNum;
    string m_name;
    U m_tTable;
};

template <class U>
Gate<U>::Gate()
{}

template <class U>
Gate<U>::Gate(U tTable, int parNum, string name) : m_tTable(tTable), m_parNum(parNum), m_name(name)
{}

template <class U>
string Gate<U>::getName()
{
    return m_name;
}

template <class U>
int Gate<U>::getPars() const
{
    return m_parNum;
}

template <class U>
bool Gate<U>::getLogic(vector<bool> b)
{
    return getLogic(b, m_tTable);
}
