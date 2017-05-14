#include "XorGate.hpp"

XorGate::XorGate() : Gate<vector<vector<bool>>>(vector<vector<bool>> {{F, T}, {T, F}}, 2, "XOR")
{}
