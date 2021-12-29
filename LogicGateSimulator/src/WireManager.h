#pragma once
#include "Wire.h"
#include <vector>
#include "Circuit.h"
class WireManager
{
public:
	static void Update();
	static void ConnectNewLine();
	static void DrawNewLine();
	static std::vector<Wire> wires;
	static int eraseIndex;
private:
	WireManager();
	static Circuit::IO* first;
	static Circuit::IO* second;
};