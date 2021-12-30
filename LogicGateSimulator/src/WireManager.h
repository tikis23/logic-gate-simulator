#pragma once
#include "Wire.h"
#include <vector>
#include "Circuit.h"
class WireManager
{
public:
	WireManager();
	~WireManager();
	void Update();
	void ConnectNewLine();
	void DrawNewLine();
	std::vector<Wire> wires;
	int eraseIndex = -1;
private:
	Circuit::IO* first;
	Circuit::IO* second;
};