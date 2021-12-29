#include "GridRenderer.h"
#include <GL/glew.h>
#include "CoordinateSystem.h"
#include "WindowManager.h"

void GridRenderer::Render()
{
	int gridSize = 200;
	int x0 = gridSize - CoordinateSystem::GetWorldCameraPosX() % gridSize - gridSize;
	int x1 = WindowManager::GetWindow("main")->GetWidth();
	int y0 = gridSize - CoordinateSystem::GetWorldCameraPosY() % gridSize - gridSize;
	int y1 = WindowManager::GetWindow("main")->GetHeight();
	glBegin(GL_LINES);
	glColor3f(0.1, 0.1, 0.1);
	for (int i = x0; i < x1; i += gridSize)
	{
		glVertex2f(CoordinateSystem::ScreenNormalizeX(i), -1);
		glVertex2f(CoordinateSystem::ScreenNormalizeX(i), 1);
	}
	for (int i = y0; i < y1; i += gridSize)
	{
		glVertex2f(-1, CoordinateSystem::ScreenNormalizeY(i));
		glVertex2f(1 , CoordinateSystem::ScreenNormalizeY(i));
	}
	glEnd();
}