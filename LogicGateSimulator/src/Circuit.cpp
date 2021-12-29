#include "Circuit.h"
#include <GL/glew.h>
#include "CoordinateSystem.h"
#include "Input.h"
#include "WindowManager.h"
#include "FontRenderer.h"
Circuit::Circuit(int inputs, int outputs, std::string name)
{
	this->name = name;
	posX = 0;
	posY = 0;
	color[0] = 0.1f;
	color[1] = 0.6f;
	color[2] = 0.4f;
	width = 50;
	int spacing = 25;
	height = std::max(inputs, outputs) * spacing;
	input.resize(inputs);
	output.resize(outputs);
	for (int i = 0; i < input.size(); i++)
	{
		input[i].type = 0;
	}
	for (int i = 0; i < output.size(); i++)
	{
		output[i].type = 1;
	}
}

Circuit::~Circuit()
{
}

bool Circuit::IsHovered()
{
	bool isHovered;
	int mx, my;
	Input::GetMousePosition(WindowManager::GetWindow("main")->GetHandle(), mx, my);
	mx = CoordinateSystem::ScreenToWorldX(mx);
	my = CoordinateSystem::ScreenToWorldY(my);
	if (mx >= posX && mx <= posX + width && my >= posY && my <= posY + height)
		isHovered = true;
	else
		isHovered = false;
	
	if (isHovered)
		hovered = this;

	return isHovered;
}

bool Circuit::IsHoveredIO()
{
	bool isHovered;
	int mx, my;
	Input::GetMousePosition(WindowManager::GetWindow("main")->GetHandle(), mx, my);
	mx = CoordinateSystem::ScreenToWorldX(mx);
	my = CoordinateSystem::ScreenToWorldY(my);
	
	for (int i = 0; i < input.size(); i++)
	{
		if (sqrtf((input[i].posX - mx) * (input[i].posX - mx) + (input[i].posY - my) * (input[i].posY - my)) <= 8)
		{
			hoveredIO = &input[i];
			return true;
		}
	}
	for (int i = 0; i < output.size(); i++)
	{
		if (sqrtf((output[i].posX - mx) * (output[i].posX - mx) + (output[i].posY - my) * (output[i].posY - my)) <= 8)
		{
			hoveredIO = &output[i];
			return true;
		}
	}

	return false;
}

void Circuit::RenderBox()
{
	glBegin(GL_QUADS);
	glColor3f(color[0], color[1], color[2]);
	glVertex2f(CoordinateSystem::ScreenNormalizeX(CoordinateSystem::WorldToScreenX(posX)), CoordinateSystem::ScreenNormalizeY(CoordinateSystem::WorldToScreenY(posY)));
	glVertex2f(CoordinateSystem::ScreenNormalizeX(CoordinateSystem::WorldToScreenX(posX + width)), CoordinateSystem::ScreenNormalizeY(CoordinateSystem::WorldToScreenY(posY)));
	glVertex2f(CoordinateSystem::ScreenNormalizeX(CoordinateSystem::WorldToScreenX(posX + width)), CoordinateSystem::ScreenNormalizeY(CoordinateSystem::WorldToScreenY(posY + height)));
	glVertex2f(CoordinateSystem::ScreenNormalizeX(CoordinateSystem::WorldToScreenX(posX)), CoordinateSystem::ScreenNormalizeY(CoordinateSystem::WorldToScreenY(posY + height)));
	glEnd();
}

void Circuit::RenderOutline()
{
	glBegin(GL_LINE_STRIP);
	glColor3f(0.2, 0.2, 0.2);
	if(hovered == this)
		glColor3f(1.0, 1.0, 1.0);
	glVertex2f(CoordinateSystem::ScreenNormalizeX(CoordinateSystem::WorldToScreenX(posX)), CoordinateSystem::ScreenNormalizeY(CoordinateSystem::WorldToScreenY(posY)));
	glVertex2f(CoordinateSystem::ScreenNormalizeX(CoordinateSystem::WorldToScreenX(posX + width)), CoordinateSystem::ScreenNormalizeY(CoordinateSystem::WorldToScreenY(posY)));
	glVertex2f(CoordinateSystem::ScreenNormalizeX(CoordinateSystem::WorldToScreenX(posX + width)), CoordinateSystem::ScreenNormalizeY(CoordinateSystem::WorldToScreenY(posY + height)));
	glVertex2f(CoordinateSystem::ScreenNormalizeX(CoordinateSystem::WorldToScreenX(posX)), CoordinateSystem::ScreenNormalizeY(CoordinateSystem::WorldToScreenY(posY + height)));
	glVertex2f(CoordinateSystem::ScreenNormalizeX(CoordinateSystem::WorldToScreenX(posX)), CoordinateSystem::ScreenNormalizeY(CoordinateSystem::WorldToScreenY(posY)));
	glEnd();
}

void Circuit::RenderIO()
{
	glPointSize(15);
	glBegin(GL_POINTS);
	glColor3f(0.8, 0.8, 0.8);
	for (int i = 0; i < input.size(); i++)
	{
		if(&input[i] == hoveredIO)
			glColor3f(1, 1, 1);
		input[i].posX = posX;
		input[i].posY = posY + height / (i + 1) - 12;
		glVertex2f(CoordinateSystem::ScreenNormalizeX(CoordinateSystem::WorldToScreenX(input[i].posX)), CoordinateSystem::ScreenNormalizeY(CoordinateSystem::WorldToScreenY(input[i].posY)));
		glColor3f(0.8, 0.8, 0.8);
	}
	for (int i = 0; i < output.size(); i++)
	{
		if (&output[i] == hoveredIO)
			glColor3f(1, 1, 1);
		output[i].posX = posX + width;
		output[i].posY = posY + height / (i + 1) - 12;
		glVertex2f(CoordinateSystem::ScreenNormalizeX(CoordinateSystem::WorldToScreenX(output[i].posX)), CoordinateSystem::ScreenNormalizeY(CoordinateSystem::WorldToScreenY(output[i].posY)));
		glColor3f(0.8, 0.8, 0.8);
	}
	glEnd();

	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(0.5, 0.5, 0.5);
	for (int i = 0; i < input.size(); i++)
		glVertex2f(CoordinateSystem::ScreenNormalizeX(CoordinateSystem::WorldToScreenX(input[i].posX)), CoordinateSystem::ScreenNormalizeY(CoordinateSystem::WorldToScreenY(input[i].posY)));
	for (int i = 0; i < output.size(); i++)
		glVertex2f(CoordinateSystem::ScreenNormalizeX(CoordinateSystem::WorldToScreenX(output[i].posX)), CoordinateSystem::ScreenNormalizeY(CoordinateSystem::WorldToScreenY(output[i].posY)));
	glEnd();
}

void Circuit::RenderFont()
{
	// name
	FontRenderer::AddToRenderQueue(name, CoordinateSystem::WorldToScreenX(posX) + width / name.size() * 0.5, CoordinateSystem::WorldToScreenY(posY) - 14);

	// IO
	for (int i = 0; i < input.size(); i++)
		FontRenderer::AddToRenderQueue(std::to_string(i), CoordinateSystem::WorldToScreenX(input[i].posX) + 8, CoordinateSystem::WorldToScreenY(input[i].posY) - 8);
	for (int i = 0; i < output.size(); i++)
		FontRenderer::AddToRenderQueue(std::to_string(i), CoordinateSystem::WorldToScreenX(output[i].posX) - 8 - (6 * std::to_string(i).size()), CoordinateSystem::WorldToScreenY(output[i].posY) - 8);
}

Circuit* Circuit::hovered;
Circuit::IO* Circuit::hoveredIO;