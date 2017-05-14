#include "MuxGate.hpp"

MuxGate::MuxGate() : Gate<vector<vector<vector<bool>>>>(vector<vector<vector<bool>>> {{{F,F},{T,T}},{{F,T},{F,T}}}, 3, "MUX")
{}
