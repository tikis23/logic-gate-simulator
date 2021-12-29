#include "Wire.h"
#include <GL/glew.h>
#include "CoordinateSystem.h"
#include "CircuitManager.h"
Wire::Wire(Circuit::IO* in, Circuit::IO* out)
{
	input = in;
	output = out;
}

Wire::~Wire()
{
}

bool Wire::Update()
{
	if (input != nullptr && output != nullptr)
	{
		val = input->value;
		if(input->value)
			output->value = input->value;
		return true;
	}
	return false;
}

void Wire::Render()
{
	if (input != nullptr && output != nullptr)
	{
		glBegin(GL_LINES);
		glColor3f(!val * 0.5, val + !val * 0.5,!val * 0.5);
		glVertex2f(CoordinateSystem::ScreenNormalizeX(CoordinateSystem::WorldToScreenX(input->posX)),
			CoordinateSystem::ScreenNormalizeY(CoordinateSystem::WorldToScreenY(input->posY)));

		glVertex2f(CoordinateSystem::ScreenNormalizeX(CoordinateSystem::WorldToScreenX(output->posX)),
			CoordinateSystem::ScreenNormalizeY(CoordinateSystem::WorldToScreenY(output->posY)));
		glEnd();
	}
}
