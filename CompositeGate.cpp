#include "CompositeGate.hpp"

CompositeGate::CompositeGate()
{}

CompositeGate::CompositeGate(vector<NTGate*> g)
{
    m_gates = g;
    
    m_parNum = 0;
    
    for (size_t i = 0; i < m_gates.size(); i++)
    {
        m_parNum += m_gates[i]->getPars();
    }
}

string CompositeGate::getName()
{
    string name;
    
    for (unsigned int i = 0; i < m_gates.size(); i++)
    {
        name.append(m_gates[i]->getName());
        name.append(" ");
    }
    
    return name;
}

vector<NTGate*> CompositeGate::getGates()
{
    return m_gates;
}

int CompositeGate::getPars() const
{
    return m_parNum;
}

bool CompositeGate::getLogic(vector<bool> params)
{
    if (params.size() != this -> m_parNum)
    {
        cout << "Incorrect number of parameters for this gate!";
        return false;
    }
    
    int paramNum = 0;
    bool gateLogic = false;
    vector<bool> gateParams;
    
    switch (m_gates[0] -> getPars())
    {
        case 1:
            gateParams.push_back(params[paramNum]);
            gateLogic = m_gates[0] -> getLogic(gateParams);
            paramNum ++;
            break;
        case 2:
            gateParams.push_back(params[paramNum]);
            gateParams.push_back(params[paramNum + 1]);
            gateLogic = m_gates[0] -> getLogic(gateParams);
            paramNum += 2;
            break;
        case 3:
            gateParams.push_back(params[paramNum]);
            gateParams.push_back(params[paramNum + 1]);
            gateParams.push_back(params[paramNum + 2]);
            gateLogic = m_gates[0] -> getLogic(gateParams);
            paramNum += 3;
            break;
    }
    
    gateParams.clear();
    gateParams.push_back(gateLogic);
    
    for (unsigned int i = 1; i < m_gates.size(); i++)
    {
        
        switch (m_gates[i] -> getPars())
        {
            case 1:
                gateLogic = m_gates[i] -> getLogic(gateParams);
                break;
            case 2:
                gateParams.push_back(params[paramNum]);
                gateLogic = m_gates[i] -> getLogic(gateParams);
                paramNum ++;
                break;
            case 3:
                gateParams.push_back(params[paramNum]);
                gateParams.push_back(params[paramNum + 1]);
                gateLogic = m_gates[i] -> getLogic(gateParams);
                paramNum += 2;
                break;
        }
    }
    
    return gateLogic;
}
