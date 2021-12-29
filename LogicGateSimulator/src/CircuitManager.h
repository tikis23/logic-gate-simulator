#pragma once

#include <unordered_map>
#include "Circuit.h"
class CircuitManager
{
public:
	CircuitManager();
	static bool UpdateHovered();
	static bool UpdateHoveredIO();
	static void RemoveCircuit(Circuit* circuit);
	static void Update();
	static void Exit();
	
	struct CircuitType
	{
		int type = 0;
		void* pointer;
	};
	static std::unordered_map<Circuit*, CircuitType> circuits;

private:

};