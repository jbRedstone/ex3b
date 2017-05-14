#include "OrGate.hpp"

OrGate::OrGate() : Gate<vector<vector<bool>>>(vector<vector<bool>> {{F, T}, {T, T}}, 2, "OR")
{}
