#include "AndGate.hpp"

AndGate::AndGate() : Gate<vector<vector<bool>>>(vector<vector<bool>> {{F, F}, {F, T}}, 2, "AND")
{}
