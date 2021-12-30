#include "Renderer.h"
#include <GL/glew.h>
#include "CircuitManager.h"
#include "GridRenderer.h"
#include "WireManager.h"
#include "Settings.h"
void Renderer::Render()
{
	GridRenderer::Render();
	for (auto& circ : CircuitManager::managers[Settings::currentMapID]->circuits)
	{
		circ.first->RenderBox();
		circ.first->RenderOutline();
		circ.first->RenderIO();
		circ.first->RenderFont();
	}
	for (int i = 0; i < CircuitManager::managers[Settings::currentMapID]->wireManager->wires.size(); i++)
	{
		CircuitManager::managers[Settings::currentMapID]->wireManager->wires[i].Render();
	}
	CircuitManager::managers[Settings::currentMapID]->wireManager->DrawNewLine();
}