#pragma once

class CoordinateSystem
{
public:
	static int WorldToScreenX(int worldX);
	static int WorldToScreenY(int worldY);
	static int ScreenToWorldX(int screenX);
	static int ScreenToWorldY(int screenY);
	static float ScreenNormalizeX(int screenX);
	static float ScreenNormalizeY(int screenY);
	static void UpdateCamera(bool isAnyHovered);
	static int GetWorldCameraPosX();
	static int GetWorldCameraPosY();
private:
	CoordinateSystem();
	static int worldCameraPosX;
	static int worldCameraPosY;
	static int oldMX;
	static int oldMY;
};