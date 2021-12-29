#include "Renderer.h"
#include <GL/glew.h>
#include "CircuitManager.h"
#include "GridRenderer.h"
#include "WireManager.h"
void Renderer::Render()
{
	GridRenderer::Render();
	for (auto& circ : CircuitManager::circuits)
	{
		circ.first->RenderBox();
		circ.first->RenderOutline();
		circ.first->RenderIO();
		circ.first->RenderFont();
	}
	for (int i = 0; i < WireManager::wires.size(); i++)
	{
		WireManager::wires[i].Render();
	}
	WireManager::DrawNewLine();
}