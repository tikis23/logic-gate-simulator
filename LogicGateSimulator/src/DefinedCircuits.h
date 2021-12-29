#pragma once
#include "Circuit.h"
#include "CircuitManager.h"
#include <vector>
namespace DefinedCircuit
{
	enum _DefinedCircuit
	{
		// custom circuit
		CUSTOM,

		// gates
		AND,
		NAND,
		OR,
		NOR,
		XOR,
		XNOR,
		NOT,

		// clocks
		Clock60Hz,
		Clock30Hz,
		Clock15Hz,

		// misc
		LED,
		ButtonPress,
		ButtonHold,
		ConstantTrue,
		ConstantFalse,
		InputNode,
		OutputNode
	};
}

void CreateDefinedCircuit(int type);

class LED
{
public:
	LED();
	~LED();
	void Update();
	Circuit* circuit;
};

class ButtonPress
{
public:
	ButtonPress();
	~ButtonPress();
	void Update();
	Circuit* circuit;
};

class ButtonHold
{
public:
	ButtonHold();
	~ButtonHold();
	void Update();
	Circuit* circuit;
};

class ConstantTrue
{
public:
	ConstantTrue();
	~ConstantTrue();
	void Update();
	Circuit* circuit;
};

class ConstantFalse
{
public:
	ConstantFalse();
	~ConstantFalse();
	void Update();
	Circuit* circuit;
};

class InputNode
{
public:
	InputNode();
	~InputNode();
	void Update();
	Circuit* circuit;
};

class OutputNode
{
public:
	OutputNode();
	~OutputNode();
	void Update();
	Circuit* circuit;
};

class Clock60Hz
{
public:
	Clock60Hz();
	~Clock60Hz();
	void Update();
	Circuit* circuit;
private:
	int counter = 0;
};

class Clock30Hz
{
public:
	Clock30Hz();
	~Clock30Hz();
	void Update();
	Circuit* circuit;
private:
	int counter = 0;
};

class Clock15Hz
{
public:
	Clock15Hz();
	~Clock15Hz();
	void Update();
	Circuit* circuit;
private:
	int counter = 0;
};

class AND
{
public:
	AND();
	~AND();
	void Update();
	Circuit* circuit;
};

class NAND
{
public:
	NAND();
	~NAND();
	void Update();
	Circuit* circuit;
};

class OR
{
public:
	OR();
	~OR();
	void Update();
	Circuit* circuit;
};

class NOR
{
public:
	NOR();
	~NOR();
	void Update();
	Circuit* circuit;
};

class XOR
{
public:
	XOR();
	~XOR();
	void Update();
	Circuit* circuit;
};

class XNOR
{
public:
	XNOR();
	~XNOR();
	void Update();
	Circuit* circuit;
};

class NOT
{
public:
	NOT();
	~NOT();
	void Update();
	Circuit* circuit;
};

class CUSTOM
{
public:
	CUSTOM();
	~CUSTOM();
	void Update();
	void EditMode();
	Circuit* circuit;
private:
	std::vector<InputNode>inputs;
	std::vector<OutputNode>output;
};