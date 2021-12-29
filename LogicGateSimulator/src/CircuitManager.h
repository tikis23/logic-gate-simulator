#pragma once

#include <unordered_map>
#include "Circuit.h"
#include "DefinedCircuits.h"
class CircuitManager
{
public:
	CircuitManager();
	~CircuitManager();
	bool UpdateHovered();
	bool UpdateHoveredIO();
	void RemoveCircuit(Circuit* circuit);
	void Update();
	void Exit();
	
	struct CircuitType
	{
		int type = 0;
		void* pointer;
	};
	std::unordered_map<Circuit*, CircuitType> circuits;
	int mapID;
	std::vector<InputNode*> inputs;
	std::vector<OutputNode*> outputs;
	static std::unordered_map<int, CircuitManager*> managers;
};