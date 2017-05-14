#include "NotGate.hpp"

NotGate::NotGate() : Gate<vector<bool>>(vector<bool> {T, F}, 1, "NOT")
{}
