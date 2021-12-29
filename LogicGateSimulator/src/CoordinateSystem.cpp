#include "CoordinateSystem.h"
#include "WindowManager.h"
#include "Input.h"
#include "Circuit.h"

int CoordinateSystem::WorldToScreenX(int worldX)
{
	return worldX - worldCameraPosX;
}

int CoordinateSystem::WorldToScreenY(int worldY)
{
	return worldY - worldCameraPosY;
}

int CoordinateSystem::ScreenToWorldX(int screenX)
{
	return screenX + worldCameraPosX;
}

int CoordinateSystem::ScreenToWorldY(int screenY)
{
	return screenY + worldCameraPosY;
}

float CoordinateSystem::ScreenNormalizeX(int screenX)
{
	return screenX / WindowManager::GetWindow("main")->GetWidth() * 2  - 1;
}

float CoordinateSystem::ScreenNormalizeY(int screenY)
{
	return screenY / WindowManager::GetWindow("main")->GetHeight() * 2 - 1;
}

void CoordinateSystem::UpdateCamera(bool isAnyHovered)
{
	int mx, my;
	Input::GetMousePosition(WindowManager::GetWindow("main")->GetHandle(), mx, my);
	if (Input::GetMouseButton(WindowManager::GetWindow("main")->GetHandle(), Input::Mouse::LEFT, Input::Action::HOLD))
	{
		if (isAnyHovered)
		{
			if (Circuit::hovered != nullptr)
			{
				Circuit::hovered->posX += mx - oldMX;
				Circuit::hovered->posY += my - oldMY;
			}
		}
		else
		{
			worldCameraPosX -= mx - oldMX;
			worldCameraPosY -= my - oldMY;
		}
	}
	oldMX = mx;
	oldMY = my;
}

int CoordinateSystem::GetWorldCameraPosX()
{
	return worldCameraPosX;
}

int CoordinateSystem::GetWorldCameraPosY()
{
	return worldCameraPosY;
}

int CoordinateSystem::worldCameraPosX = -400;
int CoordinateSystem::worldCameraPosY = -400;
int CoordinateSystem::oldMX = 0;
int CoordinateSystem::oldMY = 0;