#include "DefinedCircuits.h"
#include "WindowManager.h"
#include "CoordinateSystem.h"
#include "Input.h"
#include "Settings.h"
#include "CircuitManager.h"
#include "WireManager.h"

void CreateDefinedCircuit(int type)
{
	switch (type)
	{
	default:
		break;
		// custom
	case DefinedCircuit::CUSTOM:
		new CUSTOM;
		break;

		// gates
	case DefinedCircuit::AND:
		new AND;
		break;
	case DefinedCircuit::NAND:
		new NAND;
		break;
	case DefinedCircuit::OR:
		new OR;
		break;
	case DefinedCircuit::NOR:
		new NOR;
		break;
	case DefinedCircuit::XOR:
		new XOR;
		break;
	case DefinedCircuit::XNOR:
		new XNOR;
		break;
	case DefinedCircuit::NOT:
		new NOT;
		break;

		// clocks
	case DefinedCircuit::Clock60Hz:
		new Clock60Hz;
		break;
	case DefinedCircuit::Clock30Hz:
		new Clock30Hz;
		break;
	case DefinedCircuit::Clock15Hz:
		new Clock15Hz;
		break;

		// misc
	case DefinedCircuit::LED:
		new LED;
		break;
	case DefinedCircuit::ButtonPress:
		new ButtonPress;
		break;
	case DefinedCircuit::ButtonHold:
		new ButtonHold;
		break;
	case DefinedCircuit::ConstantTrue:
		new ConstantTrue;
		break;
	case DefinedCircuit::ConstantFalse:
		new ConstantFalse;
		break;
	case DefinedCircuit::InputNode:
		new InputNode;
		break;
	case DefinedCircuit::OutputNode:
		new OutputNode;
		break;
	}
}

Circuit* DuplicateDefinedCircuit(int type, void* ptr)
{
	switch (type)
	{
	default:
		break;
		// custom
	case DefinedCircuit::CUSTOM:
		return ((CUSTOM*)ptr)->Duplicate();
		break;

		// gates
	case DefinedCircuit::AND:
		return ((AND*)ptr)->Duplicate();
		break;
	case DefinedCircuit::NAND:
		return ((NAND*)ptr)->Duplicate();
		break;
	case DefinedCircuit::OR:
		return ((OR*)ptr)->Duplicate();
		break;
	case DefinedCircuit::NOR:
		return ((NOR*)ptr)->Duplicate();
		break;
	case DefinedCircuit::XOR:
		return ((XOR*)ptr)->Duplicate();
		break;
	case DefinedCircuit::XNOR:
		return ((XNOR*)ptr)->Duplicate();
		break;
	case DefinedCircuit::NOT:
		return ((NOT*)ptr)->Duplicate();
		break;

		// clocks
	case DefinedCircuit::Clock60Hz:
		return ((Clock60Hz*)ptr)->Duplicate();
		break;
	case DefinedCircuit::Clock30Hz:
		return ((Clock30Hz*)ptr)->Duplicate();
		break;
	case DefinedCircuit::Clock15Hz:
		return ((Clock15Hz*)ptr)->Duplicate();
		break;

		// misc
	case DefinedCircuit::LED:
		return ((LED*)ptr)->Duplicate();
		break;
	case DefinedCircuit::ButtonPress:
		return ((ButtonPress*)ptr)->Duplicate();
		break;
	case DefinedCircuit::ButtonHold:
		return ((ButtonHold*)ptr)->Duplicate();
		break;
	case DefinedCircuit::ConstantTrue:
		return ((ConstantTrue*)ptr)->Duplicate();
		break;
	case DefinedCircuit::ConstantFalse:
		return ((ConstantFalse*)ptr)->Duplicate();
		break;
	case DefinedCircuit::InputNode:
		return ((InputNode*)ptr)->Duplicate();
		break;
	case DefinedCircuit::OutputNode:
		return ((OutputNode*)ptr)->Duplicate();
		break;
	}
}

LED::LED()
{
	circuit = new Circuit{ 1, 0, "LED"};
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].type = DefinedCircuit::LED;
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].pointer = this;
	circuit->color[0] = 0.1f;
	circuit->color[1] = 0.1f;
	circuit->color[2] = 0.1f;
}
LED::~LED()
{
	CircuitManager::managers[Settings::currentMapID]->circuits.erase(circuit);
	delete circuit;
}
void LED::Update()
{
	if (circuit->input[0].value)
		circuit->color[0] = 1.0f;
	else
		circuit->color[0] = 0.0f;
	circuit->input[0].value = false;
}
Circuit* LED::Duplicate()
{
	LED* temp = new LED;
	*temp->circuit = *circuit;
	return temp->circuit;
}

ButtonPress::ButtonPress()
{
	circuit = new Circuit{ 0, 1, "ButtonPress"};
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].type = DefinedCircuit::ButtonPress;
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].pointer = this;
	circuit->color[0] = 0.5f;
	circuit->color[1] = 0.0f;
	circuit->color[2] = 0.0f;
}
ButtonPress::~ButtonPress()
{
	CircuitManager::managers[Settings::currentMapID]->circuits.erase(circuit);
	delete circuit;
}
void ButtonPress::Update()
{
}
Circuit* ButtonPress::Duplicate()
{
	ButtonPress* temp = new ButtonPress;
	*temp->circuit = *circuit;
	return temp->circuit;
}

ButtonHold::ButtonHold()
{
	circuit = new Circuit{ 0, 1, "ButtonHold"};
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].type = DefinedCircuit::ButtonHold;
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].pointer = this;
	circuit->color[0] = 0.5f;
	circuit->color[1] = 0.0f;
	circuit->color[2] = 0.5f;
}
ButtonHold::~ButtonHold()
{
	CircuitManager::managers[Settings::currentMapID]->circuits.erase(circuit);
	delete circuit;
}
void ButtonHold::Update()
{
	if (Input::GetMouseButton(WindowManager::GetWindow("main")->GetHandle(), Input::Mouse::LEFT, Input::Action::HOLD))
	{
		if (Circuit::hovered == circuit)
		{
			circuit->output[0].value = true;
			circuit->color[0] = 1.0f;
			circuit->color[2] = 1.0f;
		}
	}
	else
	{
		circuit->output[0].value = false;
		circuit->color[0] = 0.5f;
		circuit->color[2] = 0.5f;
	}
}
Circuit* ButtonHold::Duplicate()
{
	ButtonHold* temp = new ButtonHold;
	*temp->circuit = *circuit;
	return temp->circuit;
}

ConstantTrue::ConstantTrue()
{
	circuit = new Circuit{ 0, 1, "ConstantTrue"};
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].type = DefinedCircuit::ConstantTrue;
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].pointer = this;
	circuit->color[0] = 1.0f;
	circuit->color[1] = 1.0f;
	circuit->color[2] = 1.0f;
	circuit->output[0].value = true;
}
ConstantTrue::~ConstantTrue()
{
	CircuitManager::managers[Settings::currentMapID]->circuits.erase(circuit);
	delete circuit;
}
void ConstantTrue::Update()
{
}
Circuit* ConstantTrue::Duplicate()
{
	ConstantTrue* temp = new ConstantTrue;
	*temp->circuit = *circuit;
	return temp->circuit;
}

ConstantFalse::ConstantFalse()
{
	circuit = new Circuit{ 0, 1, "ConstantFalse"};
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].type = DefinedCircuit::ConstantFalse;
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].pointer = this;
	circuit->color[0] = 0.2f;
	circuit->color[1] = 0.2f;
	circuit->color[2] = 0.2f;
	circuit->output[0].value = false;
}
ConstantFalse::~ConstantFalse()
{
	CircuitManager::managers[Settings::currentMapID]->circuits.erase(circuit);
	delete circuit;
}
void ConstantFalse::Update()
{
}
Circuit* ConstantFalse::Duplicate()
{
	ConstantFalse* temp = new ConstantFalse;
	*temp->circuit = *circuit;
	return temp->circuit;
}

InputNode::InputNode()
{
	circuit = new Circuit{ 0, 1, "Input" };
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].type = DefinedCircuit::InputNode;
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].pointer = this;
	circuit->color[0] = 0.5f;
	circuit->color[1] = 0.0f;
	circuit->color[2] = 0.0f;
	CircuitManager::managers[Settings::currentMapID]->inputs.push_back(this);
	circuit->name += " " + std::to_string(CircuitManager::managers[Settings::currentMapID]->inputs.size() - 1);
}
InputNode::~InputNode()
{
	for(int i = 0; i < CircuitManager::managers[Settings::currentMapID]->inputs.size(); i++)
		if (CircuitManager::managers[Settings::currentMapID]->inputs[i] == this)
		{
			CircuitManager::managers[Settings::currentMapID]->inputs.erase(CircuitManager::managers[Settings::currentMapID]->inputs.begin() + i);
			break;
		}
	CircuitManager::managers[Settings::currentMapID]->circuits.erase(circuit);
	for (int i = 0; i < CircuitManager::managers[Settings::currentMapID]->inputs.size(); i++)
		CircuitManager::managers[Settings::currentMapID]->inputs[i]->circuit->name = "Input " + std::to_string(i);
	delete circuit;
}
void InputNode::Update()
{
}
Circuit* InputNode::Duplicate()
{
	InputNode* temp = new InputNode;
	*temp->circuit = *circuit;
	return temp->circuit;
}

OutputNode::OutputNode()
{
	circuit = new Circuit{ 1, 0, "Output" };
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].type = DefinedCircuit::OutputNode;
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].pointer = this;
	circuit->color[0] = 0.0f;
	circuit->color[1] = 0.5f;
	circuit->color[2] = 0.0f;
	CircuitManager::managers[Settings::currentMapID]->outputs.push_back(this);
	circuit->name += " " + std::to_string(CircuitManager::managers[Settings::currentMapID]->outputs.size() - 1);
}
OutputNode::~OutputNode()
{
	for (int i = 0; i < CircuitManager::managers[Settings::currentMapID]->outputs.size(); i++)
		if (CircuitManager::managers[Settings::currentMapID]->outputs[i] == this)
		{
			CircuitManager::managers[Settings::currentMapID]->outputs.erase(CircuitManager::managers[Settings::currentMapID]->outputs.begin() + i);
			break;
		}
	CircuitManager::managers[Settings::currentMapID]->circuits.erase(circuit);
	for (int i = 0; i < CircuitManager::managers[Settings::currentMapID]->outputs.size(); i++)
		CircuitManager::managers[Settings::currentMapID]->outputs[i]->circuit->name = "Output " + std::to_string(i);
	delete circuit;
}
void OutputNode::Update()
{
}
Circuit* OutputNode::Duplicate()
{
	OutputNode* temp = new OutputNode;
	*temp->circuit = *circuit;
	return temp->circuit;
}

Clock60Hz::Clock60Hz()
{
	circuit = new Circuit{ 0, 1, "Clock60Hz"};
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].type = DefinedCircuit::Clock60Hz;
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].pointer = this;
	circuit->color[0] = 1.0f;
	circuit->color[1] = 1.0f;
	circuit->color[2] = 0.0f;
}
Clock60Hz::~Clock60Hz()
{
	CircuitManager::managers[Settings::currentMapID]->circuits.erase(circuit);
	delete circuit;
}
void Clock60Hz::Update()
{
	if (counter == 1)
	{
		circuit->output[0].value = !circuit->output[0].value;
		counter = 0;
	}
	counter++;
}
Circuit* Clock60Hz::Duplicate()
{
	Clock60Hz* temp = new Clock60Hz;
	*temp->circuit = *circuit;
	return temp->circuit;
}

Clock30Hz::Clock30Hz()
{
	circuit = new Circuit{ 0, 1, "Clock30Hz"};
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].type = DefinedCircuit::Clock30Hz;
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].pointer = this;
	circuit->color[0] = 0.5f;
	circuit->color[1] = 0.5f;
	circuit->color[2] = 0.0f;
}
Clock30Hz::~Clock30Hz()
{
	CircuitManager::managers[Settings::currentMapID]->circuits.erase(circuit);
	delete circuit;
}
void Clock30Hz::Update()
{
	if (counter == 2)
	{
		circuit->output[0].value = !circuit->output[0].value;
		counter = 0;
	}
	counter++;
}
Circuit* Clock30Hz::Duplicate()
{
	Clock30Hz* temp = new Clock30Hz;
	*temp->circuit = *circuit;
	return temp->circuit;
}

Clock15Hz::Clock15Hz()
{
	circuit = new Circuit{ 0, 1, "Clock15Hz"};
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].type = DefinedCircuit::Clock15Hz;
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].pointer = this;
	circuit->color[0] = 0.25f;
	circuit->color[1] = 0.25f;
	circuit->color[2] = 0.0f;
}
Clock15Hz::~Clock15Hz()
{
	CircuitManager::managers[Settings::currentMapID]->circuits.erase(circuit);
	delete circuit;
}
void Clock15Hz::Update()
{
	if (counter == 4)
	{
		circuit->output[0].value = !circuit->output[0].value;
		counter = 0;
	}
	counter++;
}
Circuit* Clock15Hz::Duplicate()
{
	Clock15Hz* temp = new Clock15Hz;
	*temp->circuit = *circuit;
	return temp->circuit;
}

AND::AND()
{
	circuit = new Circuit{ 2, 1, "AND"};
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].type = DefinedCircuit::AND;
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].pointer = this;
	circuit->color[0] = 0.2f;
	circuit->color[1] = 0.2f;
	circuit->color[2] = 0.5f;
}
AND::~AND()
{
	CircuitManager::managers[Settings::currentMapID]->circuits.erase(circuit);
	delete circuit;
}
void AND::Update()
{
	if (circuit->input[0].value && circuit->input[1].value)
		circuit->output[0].value = true;
	else
		circuit->output[0].value = false;
	circuit->input[0].value = false;
	circuit->input[1].value = false;
}
Circuit* AND::Duplicate()
{
	AND* temp = new AND;
	*temp->circuit = *circuit;
	return temp->circuit;
}

NAND::NAND()
{
	circuit = new Circuit{ 2, 1 , "NAND"};
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].type = DefinedCircuit::NAND;
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].pointer = this;
	circuit->color[0] = 0.2f;
	circuit->color[1] = 0.2f;
	circuit->color[2] = 0.5f;
}
NAND::~NAND()
{
	CircuitManager::managers[Settings::currentMapID]->circuits.erase(circuit);
	delete circuit;
}
void NAND::Update()
{
	if (!(circuit->input[0].value && circuit->input[1].value))
		circuit->output[0].value = true;
	else
		circuit->output[0].value = false;
	circuit->input[0].value = false;
	circuit->input[1].value = false;
}
Circuit* NAND::Duplicate()
{
	NAND* temp = new NAND;
	*temp->circuit = *circuit;
	return temp->circuit;
}

OR::OR()
{
	circuit = new Circuit{ 2, 1, "OR"};
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].type = DefinedCircuit::OR;
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].pointer = this;
	circuit->color[0] = 0.8f;
	circuit->color[1] = 0.0f;
	circuit->color[2] = 0.8f;
}
OR::~OR()
{
	CircuitManager::managers[Settings::currentMapID]->circuits.erase(circuit);
	delete circuit;
}
void OR::Update()
{
	if (circuit->input[0].value || circuit->input[1].value)
		circuit->output[0].value = true;
	else
		circuit->output[0].value = false;

	circuit->input[0].value = false;
	circuit->input[1].value = false;
}
Circuit* OR::Duplicate()
{
	OR* temp = new OR;
	*temp->circuit = *circuit;
	return temp->circuit;
}

NOR::NOR()
{
	circuit = new Circuit{ 2, 1, "NOR"};
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].type = DefinedCircuit::NOR;
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].pointer = this;
	circuit->color[0] = 0.8f;
	circuit->color[1] = 0.0f;
	circuit->color[2] = 0.8f;
}
NOR::~NOR()
{
	CircuitManager::managers[Settings::currentMapID]->circuits.erase(circuit);
	delete circuit;
}
void NOR::Update()
{
	if (!(circuit->input[0].value || circuit->input[1].value))
		circuit->output[0].value = true;
	else
		circuit->output[0].value = false;

	circuit->input[0].value = false;
	circuit->input[1].value = false;
}
Circuit* NOR::Duplicate()
{
	NOR* temp = new NOR;
	*temp->circuit = *circuit;
	return temp->circuit;
}

XOR::XOR()
{
	circuit = new Circuit{ 2, 1, "XOR"};
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].type = DefinedCircuit::XOR;
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].pointer = this;
	circuit->color[0] = 0.8f;
	circuit->color[1] = 0.0f;
	circuit->color[2] = 0.8f;
}
XOR::~XOR()
{
	CircuitManager::managers[Settings::currentMapID]->circuits.erase(circuit);
	delete circuit;
}
void XOR::Update()
{
	if ((circuit->input[0].value || circuit->input[1].value) && !(circuit->input[0].value && circuit->input[1].value))
		circuit->output[0].value = true;
	else
		circuit->output[0].value = false;

	circuit->input[0].value = false;
	circuit->input[1].value = false;
}
Circuit* XOR::Duplicate()
{
	XOR* temp = new XOR;
	*temp->circuit = *circuit;
	return temp->circuit;
}

XNOR::XNOR()
{
	circuit = new Circuit{ 2, 1, "XNOR"};
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].type = DefinedCircuit::XNOR;
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].pointer = this;
	circuit->color[0] = 0.8f;
	circuit->color[1] = 0.0f;
	circuit->color[2] = 0.8f;
}
XNOR::~XNOR()
{
	CircuitManager::managers[Settings::currentMapID]->circuits.erase(circuit);
	delete circuit;
}
void XNOR::Update()
{
	if ((circuit->input[0].value || circuit->input[1].value) && !(circuit->input[0].value && circuit->input[1].value))
		circuit->output[0].value = false;
	else
		circuit->output[0].value = true;

	circuit->input[0].value = false;
	circuit->input[1].value = false;
}
Circuit* XNOR::Duplicate()
{
	XNOR* temp = new XNOR;
	*temp->circuit = *circuit;
	return temp->circuit;
}

NOT::NOT()
{
	circuit = new Circuit{ 1, 1, "NOT"};
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].type = DefinedCircuit::NOT;
	CircuitManager::managers[Settings::currentMapID]->circuits[circuit].pointer = this;
	circuit->color[0] = 0.0f;
	circuit->color[1] = 0.8f;
	circuit->color[2] = 0.8f;
}
NOT::~NOT()
{
	CircuitManager::managers[Settings::currentMapID]->circuits.erase(circuit);
	delete circuit;
}
void NOT::Update()
{
	circuit->output[0].value = !circuit->input[0].value;
	circuit->input[0].value = false;
}
Circuit* NOT::Duplicate()
{
	NOT* temp = new NOT;
	*temp->circuit = *circuit;
	return temp->circuit;
}

CUSTOM::CUSTOM()
{
	internalMapID = (new CircuitManager)->mapID;
	circuit = new Circuit{ 0, 0, "CUSTOM" };
	mapID = Settings::currentMapID;
	CircuitManager::managers[mapID]->circuits[circuit].type = DefinedCircuit::CUSTOM;
	CircuitManager::managers[mapID]->circuits[circuit].pointer = this;
	circuit->color[0] = 0.1f;
	circuit->color[1] = 1.0f;
	circuit->color[2] = 0.1f;
	circuit->width = 50;
	circuit->height = 50;
}
CUSTOM::~CUSTOM()
{
	delete CircuitManager::managers[internalMapID];
	CircuitManager::managers[mapID]->circuits.erase(circuit);
	delete circuit;
}
void CUSTOM::Update()
{
	UpdateIO();
	for (int i = 0; i < circuit->output.size(); i++)
		CircuitManager::managers[internalMapID]->outputs[i]->circuit->input[0].value = false;
	for (int i = 0; i < circuit->input.size(); i++)
		CircuitManager::managers[internalMapID]->inputs[i]->circuit->output[0].value = circuit->input[i].value;


	CircuitManager::managers[internalMapID]->wireManager->Update();
	// update circuits
	CircuitManager::managers[internalMapID]->Update();
	// update wires
	CircuitManager::managers[internalMapID]->wireManager->Update();


	for (int i = 0; i < circuit->output.size(); i++)
		circuit->output[i].value = CircuitManager::managers[internalMapID]->outputs[i]->circuit->input[0].value;
	for (int i = 0; i < circuit->input.size(); i++)
		circuit->input[i].value = false;
}
void CUSTOM::UpdateIO()
{
	if (CircuitManager::managers[internalMapID]->inputs.size() != circuit->input.size())
	{
		circuit->input.resize(CircuitManager::managers[internalMapID]->inputs.size());
		for (int i = 0; i < circuit->input.size(); i++)
		{
			circuit->input[i].type = 0;
			circuit->input[i].fromCircuit = circuit;
			circuit->input[i].index = i;
		}
		int spacing = 25;
		circuit->height = std::max(circuit->input.size(), circuit->output.size()) * spacing;
	}
	if (CircuitManager::managers[internalMapID]->outputs.size() != circuit->output.size())
	{
		circuit->output.resize(CircuitManager::managers[internalMapID]->outputs.size());
		for (int i = 0; i < circuit->output.size(); i++)
		{
			circuit->output[i].type = 1;
			circuit->output[i].fromCircuit = circuit;
			circuit->output[i].index = i;
		}
		int spacing = 25;
		circuit->height = std::max(circuit->input.size(), circuit->output.size()) * spacing;
	}

}
void CUSTOM::EnterEditMode()
{
	Settings::currentMapID = internalMapID;

}
void CUSTOM::ExitEditMode()
{
	Settings::currentMapID = mapID;
}
Circuit* CUSTOM::Duplicate()
{
	CUSTOM* temp = new CUSTOM;
	*temp->circuit = *circuit;

	// copy map
	int tempID = Settings::currentMapID;
	Settings::currentMapID = temp->internalMapID;
	CircuitManager* copyTo = CircuitManager::managers[temp->internalMapID];
	CircuitManager* copyFrom = CircuitManager::managers[internalMapID];

	// copy circuits
	std::unordered_map<Circuit*, Circuit*> wiringMap;
	for (auto& it : copyFrom->circuits)
		wiringMap[it.first] = DuplicateDefinedCircuit(it.second.type, it.second.pointer);
	temp->UpdateIO();
	
	// copy wires
	for (auto& it : copyFrom->wireManager->wires)
	{
		Circuit* wireFrom = wiringMap[it.input->fromCircuit];
		Circuit* wireTo = wiringMap[it.output->fromCircuit];
		copyTo->wireManager->wires.push_back(Wire{ &wireFrom->output[it.input->index], &wireTo->input[it.output->index] });
		copyTo->wireManager->wires.back().input->fromCircuit = wireFrom;
		copyTo->wireManager->wires.back().input->index = it.input->index;
		copyTo->wireManager->wires.back().output->fromCircuit = wireTo;
		copyTo->wireManager->wires.back().output->index = it.output->index;
	}
	// exit
	Settings::currentMapID = tempID;
	return temp->circuit;
}