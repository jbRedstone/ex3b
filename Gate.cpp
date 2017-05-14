#include "Gate.hpp"

template <>
bool Gate<vector<bool>>::getLogic(vector<bool> b, vector<bool> tTable)
{
    return (m_tTable)[b[0]];
}

template<>
bool Gate<vector<vector<bool>>>::getLogic(vector<bool> b, vector<vector<bool>> tTable)
{
    return (m_tTable)[b[0]][b[1]];
}

template <>
bool Gate<vector<vector<vector<bool>>>>::getLogic(vector<bool> b, vector<vector<vector<bool>>> tTable)
{
    return (m_tTable)[b[0]][b[1]][b[2]];
}
