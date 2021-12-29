#include "WireManager.h"
#include "Input.h"
#include "WindowManager.h"
#include "CoordinateSystem.h"

void WireManager::Update()
{
	if (eraseIndex >= 0)
	{
		wires[eraseIndex].output->value = 0;
		wires.erase(wires.begin() + eraseIndex);
		eraseIndex = -1;
	}
	for (int i = 0; i < wires.size(); i++)
	{
		if (!wires[i].Update())
		{
			wires.erase(wires.begin() + i);
			i--;
		}
	}
	if (first != nullptr && second != nullptr)
	{
		if (first->type)
			wires.push_back(Wire(first, second));
		else
			wires.push_back(Wire(second, first));

		first = nullptr;
		second = nullptr;
	}
}

void WireManager::ConnectNewLine()
{
	if (Input::GetMouseButton(WindowManager::GetWindow("main")->GetHandle(), Input::Mouse::RIGHT, Input::Action::PRESS))
	{
		first = nullptr;
		second = nullptr;
		if (Circuit::hoveredIO != nullptr)
		{
			for (int i = 0; i < wires.size(); i++)
			{
				if (wires[i].input == Circuit::hoveredIO || wires[i].output == Circuit::hoveredIO)
				{
					eraseIndex = i;
					break;
				}
			}
		}
	}
	else if (Circuit::hoveredIO != nullptr)
	{
		if (Input::GetMouseButton(WindowManager::GetWindow("main")->GetHandle(), Input::Mouse::LEFT, Input::Action::PRESS))
		{
			if (first == nullptr)
			{
				first = Circuit::hoveredIO;
			}
			else if (first != Circuit::hoveredIO && first->type != Circuit::hoveredIO->type)
			{
				second = Circuit::hoveredIO;
			}
		}
	}
}

void WireManager::DrawNewLine()
{
	if (first != nullptr)
	{
		int mx, my;
		Input::GetMousePosition(WindowManager::GetWindow("main")->GetHandle(), mx, my);
		glBegin(GL_LINES);
		glColor3f(0, 0, 1);
		glVertex2f(CoordinateSystem::ScreenNormalizeX(CoordinateSystem::WorldToScreenX(first->posX)), CoordinateSystem::ScreenNormalizeY(CoordinateSystem::WorldToScreenY(first->posY)));
		glVertex2f(CoordinateSystem::ScreenNormalizeX(mx), CoordinateSystem::ScreenNormalizeY(my));
		glEnd();
	}
}

int WireManager::eraseIndex = -1;
std::vector<Wire> WireManager::wires;
Circuit::IO* WireManager::first;
Circuit::IO* WireManager::second;