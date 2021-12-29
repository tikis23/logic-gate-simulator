#include "CircuitManager.h"
#include "DefinedCircuits.h"

CircuitManager::CircuitManager()
{

}

bool CircuitManager::UpdateHovered()
{
	Circuit::hovered = nullptr;
	for (auto& circ : circuits)
	{
		if (circ.first->IsHovered())
		{
			return true;
		}
	}
	return false;
}

bool CircuitManager::UpdateHoveredIO()
{
	Circuit::hoveredIO = nullptr;
	for (auto& circ : circuits)
	{
		if (circ.first->IsHoveredIO())
		{
			return true;
		}
	}
	return false;
}

void CircuitManager::RemoveCircuit(Circuit* circuit)
{
	auto it = circuits.find(circuit);
	if (it != circuits.end())
	{
		switch (it->second.type)
		{
		default:
			break;
			// custom
		case DefinedCircuit::CUSTOM:
			delete (CUSTOM*)it->second.pointer;
			break;
			// gates
		case DefinedCircuit::AND:
			delete (AND*)it->second.pointer;
			break;
		case DefinedCircuit::NAND:
			delete (NAND*)it->second.pointer;
			break;
		case DefinedCircuit::OR:
			delete (OR*)it->second.pointer;
			break;
		case DefinedCircuit::NOR:
			delete (NOR*)it->second.pointer;
			break;
		case DefinedCircuit::XOR:
			delete (XOR*)it->second.pointer;
			break;
		case DefinedCircuit::XNOR:
			delete (XNOR*)it->second.pointer;
			break;
		case DefinedCircuit::NOT:
			delete (NOT*)it->second.pointer;
			break;

			// clocks
		case DefinedCircuit::Clock60Hz:
			delete (Clock60Hz*)it->second.pointer;
			break;
		case DefinedCircuit::Clock30Hz:
			delete (Clock30Hz*)it->second.pointer;
			break;
		case DefinedCircuit::Clock15Hz:
			delete (Clock15Hz*)it->second.pointer;
			break;

			// misc
		case DefinedCircuit::LED:
			delete (LED*)it->second.pointer;
			break;
		case DefinedCircuit::ButtonPress:
			delete (ButtonPress*)it->second.pointer;
			break;
		case DefinedCircuit::ButtonHold:
			delete (ButtonHold*)it->second.pointer;
			break;
		case DefinedCircuit::ConstantTrue:
			delete (ConstantTrue*)it->second.pointer;
			break;
		case DefinedCircuit::ConstantFalse:
			delete (ConstantFalse*)it->second.pointer;
			break;
		case DefinedCircuit::InputNode:
			delete (InputNode*)it->second.pointer;
			break;
		case DefinedCircuit::OutputNode:
			delete (OutputNode*)it->second.pointer;
			break;
		} 
		circuits.erase(circuit);
	}
}

void CircuitManager::Update()
{
	for (auto& circ : circuits)
	{
		switch (circ.second.type)
		{
		default:
			break;
			// custom
		case DefinedCircuit::CUSTOM:
			((CUSTOM*)circ.second.pointer)->Update();
			break;
			// gates
		case DefinedCircuit::AND:
			((AND*)circ.second.pointer)->Update();
			break;		
		case DefinedCircuit::NAND:
			((NAND*)circ.second.pointer)->Update();
			break;
		case DefinedCircuit::OR:
			((OR*)circ.second.pointer)->Update();
			break;
		case DefinedCircuit::NOR:
			((NOR*)circ.second.pointer)->Update();
			break;
		case DefinedCircuit::XOR:
			((XOR*)circ.second.pointer)->Update();
			break;
		case DefinedCircuit::XNOR:
			((XNOR*)circ.second.pointer)->Update();
			break;
		case DefinedCircuit::NOT:
			((NOT*)circ.second.pointer)->Update();
			break;

			// clocks
		case DefinedCircuit::Clock60Hz:
			((Clock60Hz*)circ.second.pointer)->Update();
			break;
		case DefinedCircuit::Clock30Hz:
			((Clock30Hz*)circ.second.pointer)->Update();
			break;
		case DefinedCircuit::Clock15Hz:
			((Clock15Hz*)circ.second.pointer)->Update();
			break;

			// misc
		case DefinedCircuit::LED:
			((LED*)circ.second.pointer)->Update();
			break;
		case DefinedCircuit::ButtonPress:
			((ButtonPress*)circ.second.pointer)->Update();
			break;
		case DefinedCircuit::ButtonHold:
			((ButtonHold*)circ.second.pointer)->Update();
			break;
		case DefinedCircuit::ConstantTrue:
			((ConstantTrue*)circ.second.pointer)->Update();
			break;
		case DefinedCircuit::ConstantFalse:
			((ConstantFalse*)circ.second.pointer)->Update();
			break;
		case DefinedCircuit::InputNode:
			((InputNode*)circ.second.pointer)->Update();
			break;
		case DefinedCircuit::OutputNode:
			((OutputNode*)circ.second.pointer)->Update();
			break;
		}
	}
}

void CircuitManager::Exit()
{
	for (auto& it : circuits)
		delete it.first;
}

std::unordered_map<Circuit*, CircuitManager::CircuitType> CircuitManager::circuits;