#pragma once

#include "CircuitManager.h"
class ImGuiManager
{
public:
	static void Init();
	static void Exit();
	static bool Update();
	static void Render();

private:
	ImGuiManager();
	static Circuit* deletableCircuit;
};