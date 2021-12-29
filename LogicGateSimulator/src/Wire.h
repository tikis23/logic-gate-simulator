#pragma once
#include "Circuit.h"
class Wire
{
public:
	Wire(Circuit::IO* in, Circuit::IO* out);
	~Wire();
	void Render();
	bool Update();
	Circuit::IO* input;
	Circuit::IO* output;
	bool val;
private:
};