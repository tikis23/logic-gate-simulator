#include "DefinedCircuits.h"
#include "WindowManager.h"
#include "CoordinateSystem.h"
#include "Input.h"

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

LED::LED()
{
	circuit = new Circuit{ 1, 0, "LED"};
	CircuitManager::circuits[circuit].type = DefinedCircuit::LED;
	CircuitManager::circuits[circuit].pointer = this;
	circuit->color[0] = 0.1f;
	circuit->color[1] = 0.1f;
	circuit->color[2] = 0.1f;
}
LED::~LED()
{
	CircuitManager::circuits.erase(circuit);
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

ButtonPress::ButtonPress()
{
	circuit = new Circuit{ 0, 1, "ButtonPress"};
	CircuitManager::circuits[circuit].type = DefinedCircuit::ButtonPress;
	CircuitManager::circuits[circuit].pointer = this;
	circuit->color[0] = 0.5f;
	circuit->color[1] = 0.0f;
	circuit->color[2] = 0.0f;
}
ButtonPress::~ButtonPress()
{
	CircuitManager::circuits.erase(circuit);
	delete circuit;
}
void ButtonPress::Update()
{
	if (Circuit::hovered == circuit)
	{
		if (Input::GetMouseButton(WindowManager::GetWindow("main")->GetHandle(), Input::Mouse::LEFT, Input::Action::PRESS))
		{
			if (circuit->output[0].value == false)
			{
				circuit->output[0].value = true;
				circuit->color[0] = 1.0f;
			}
			else
			{
				circuit->output[0].value = false;
				circuit->color[0] = 0.5f;
			}
		}
	}
}

ButtonHold::ButtonHold()
{
	circuit = new Circuit{ 0, 1, "ButtonHold"};
	CircuitManager::circuits[circuit].type = DefinedCircuit::ButtonHold;
	CircuitManager::circuits[circuit].pointer = this;
	circuit->color[0] = 0.5f;
	circuit->color[1] = 0.0f;
	circuit->color[2] = 0.5f;
}
ButtonHold::~ButtonHold()
{
	CircuitManager::circuits.erase(circuit);
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

ConstantTrue::ConstantTrue()
{
	circuit = new Circuit{ 0, 1, "ConstantTrue"};
	CircuitManager::circuits[circuit].type = DefinedCircuit::ConstantTrue;
	CircuitManager::circuits[circuit].pointer = this;
	circuit->color[0] = 1.0f;
	circuit->color[1] = 1.0f;
	circuit->color[2] = 1.0f;
	circuit->output[0].value = true;
}
ConstantTrue::~ConstantTrue()
{
	CircuitManager::circuits.erase(circuit);
	delete circuit;
}
void ConstantTrue::Update()
{
}

ConstantFalse::ConstantFalse()
{
	circuit = new Circuit{ 0, 1, "ConstantFalse"};
	CircuitManager::circuits[circuit].type = DefinedCircuit::ConstantFalse;
	CircuitManager::circuits[circuit].pointer = this;
	circuit->color[0] = 0.2f;
	circuit->color[1] = 0.2f;
	circuit->color[2] = 0.2f;
	circuit->output[0].value = false;
}
ConstantFalse::~ConstantFalse()
{
	CircuitManager::circuits.erase(circuit);
	delete circuit;
}
void ConstantFalse::Update()
{
}

InputNode::InputNode()
{
	circuit = new Circuit{ 0, 1, "InputNode" };
	CircuitManager::circuits[circuit].type = DefinedCircuit::InputNode;
	CircuitManager::circuits[circuit].pointer = this;
	circuit->color[0] = 0.5f;
	circuit->color[1] = 0.0f;
	circuit->color[2] = 0.0f;
}
InputNode::~InputNode()
{
	CircuitManager::circuits.erase(circuit);
	delete circuit;
}
void InputNode::Update()
{
}

OutputNode::OutputNode()
{
	circuit = new Circuit{ 1, 0, "OutputNode" };
	CircuitManager::circuits[circuit].type = DefinedCircuit::OutputNode;
	CircuitManager::circuits[circuit].pointer = this;
	circuit->color[0] = 0.0f;
	circuit->color[1] = 0.5f;
	circuit->color[2] = 0.0f;
}
OutputNode::~OutputNode()
{
	CircuitManager::circuits.erase(circuit);
	delete circuit;
}
void OutputNode::Update()
{
}

Clock60Hz::Clock60Hz()
{
	circuit = new Circuit{ 0, 1, "Clock60Hz"};
	CircuitManager::circuits[circuit].type = DefinedCircuit::Clock60Hz;
	CircuitManager::circuits[circuit].pointer = this;
	circuit->color[0] = 1.0f;
	circuit->color[1] = 1.0f;
	circuit->color[2] = 0.0f;
}
Clock60Hz::~Clock60Hz()
{
	CircuitManager::circuits.erase(circuit);
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

Clock30Hz::Clock30Hz()
{
	circuit = new Circuit{ 0, 1, "Clock30Hz"};
	CircuitManager::circuits[circuit].type = DefinedCircuit::Clock30Hz;
	CircuitManager::circuits[circuit].pointer = this;
	circuit->color[0] = 0.5f;
	circuit->color[1] = 0.5f;
	circuit->color[2] = 0.0f;
}
Clock30Hz::~Clock30Hz()
{
	CircuitManager::circuits.erase(circuit);
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

Clock15Hz::Clock15Hz()
{
	circuit = new Circuit{ 0, 1, "Clock15Hz"};
	CircuitManager::circuits[circuit].type = DefinedCircuit::Clock15Hz;
	CircuitManager::circuits[circuit].pointer = this;
	circuit->color[0] = 0.25f;
	circuit->color[1] = 0.25f;
	circuit->color[2] = 0.0f;
}
Clock15Hz::~Clock15Hz()
{
	CircuitManager::circuits.erase(circuit);
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

AND::AND()
{
	circuit = new Circuit{ 2, 1, "AND"};
	CircuitManager::circuits[circuit].type = DefinedCircuit::AND;
	CircuitManager::circuits[circuit].pointer = this;
	circuit->color[0] = 0.2f;
	circuit->color[1] = 0.2f;
	circuit->color[2] = 0.5f;
}
AND::~AND()
{
	CircuitManager::circuits.erase(circuit);
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

NAND::NAND()
{
	circuit = new Circuit{ 2, 1 , "NAND"};
	CircuitManager::circuits[circuit].type = DefinedCircuit::NAND;
	CircuitManager::circuits[circuit].pointer = this;
	circuit->color[0] = 0.2f;
	circuit->color[1] = 0.2f;
	circuit->color[2] = 0.5f;
}
NAND::~NAND()
{
	CircuitManager::circuits.erase(circuit);
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

OR::OR()
{
	circuit = new Circuit{ 2, 1, "OR"};
	CircuitManager::circuits[circuit].type = DefinedCircuit::OR;
	CircuitManager::circuits[circuit].pointer = this;
	circuit->color[0] = 0.8f;
	circuit->color[1] = 0.0f;
	circuit->color[2] = 0.8f;
}
OR::~OR()
{
	CircuitManager::circuits.erase(circuit);
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

NOR::NOR()
{
	circuit = new Circuit{ 2, 1, "NOR"};
	CircuitManager::circuits[circuit].type = DefinedCircuit::NOR;
	CircuitManager::circuits[circuit].pointer = this;
	circuit->color[0] = 0.8f;
	circuit->color[1] = 0.0f;
	circuit->color[2] = 0.8f;
}
NOR::~NOR()
{
	CircuitManager::circuits.erase(circuit);
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

XOR::XOR()
{
	circuit = new Circuit{ 2, 1, "XOR"};
	CircuitManager::circuits[circuit].type = DefinedCircuit::XOR;
	CircuitManager::circuits[circuit].pointer = this;
	circuit->color[0] = 0.8f;
	circuit->color[1] = 0.0f;
	circuit->color[2] = 0.8f;
}
XOR::~XOR()
{
	CircuitManager::circuits.erase(circuit);
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

XNOR::XNOR()
{
	circuit = new Circuit{ 2, 1, "XNOR"};
	CircuitManager::circuits[circuit].type = DefinedCircuit::XNOR;
	CircuitManager::circuits[circuit].pointer = this;
	circuit->color[0] = 0.8f;
	circuit->color[1] = 0.0f;
	circuit->color[2] = 0.8f;
}
XNOR::~XNOR()
{
	CircuitManager::circuits.erase(circuit);
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

NOT::NOT()
{
	circuit = new Circuit{ 1, 1, "NOT"};
	CircuitManager::circuits[circuit].type = DefinedCircuit::NOT;
	CircuitManager::circuits[circuit].pointer = this;
	circuit->color[0] = 0.0f;
	circuit->color[1] = 0.8f;
	circuit->color[2] = 0.8f;
}
NOT::~NOT()
{
	CircuitManager::circuits.erase(circuit);
	delete circuit;
}
void NOT::Update()
{
	circuit->output[0].value = !circuit->input[0].value;
	circuit->input[0].value = false;
}

CUSTOM::CUSTOM()
{
	circuit = new Circuit{ 0, 0, "CUSTOM" };
	CircuitManager::circuits[circuit].type = DefinedCircuit::CUSTOM;
	CircuitManager::circuits[circuit].pointer = this;
	circuit->color[0] = 0.1f;
	circuit->color[1] = 1.0f;
	circuit->color[2] = 0.1f;
	circuit->width = 50;
	circuit->height = 50;
}
CUSTOM::~CUSTOM()
{
	CircuitManager::circuits.erase(circuit);
	delete circuit;
}
void CUSTOM::Update()
{
}
void CUSTOM::EditMode()
{

}