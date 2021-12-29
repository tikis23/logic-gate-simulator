#include "Program.h"

#include <string>
#include <time.h>
#include <thread>
#include <chrono>

#include "WindowManager.h"
#include "Input.h"
#include "Settings.h"
#include "Renderer.h"
#include "CoordinateSystem.h"
#include "CircuitManager.h"
#include "ImGuiManager.h"
#include "WireManager.h"
#include "DefinedCircuits.h"
#include "FontRenderer.h"

void error_callback(int error, const char* msg) {
	std::string s;
	s = " [" + std::to_string(error) + "] " + msg + '\n';
	MessageBoxA(0, s.c_str(), "GLFW error", MB_OK);
}

Program::Program()
{
	running = true;
	// init glfw
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		running = false;
		MessageBoxA(0, "GLFWInit != GLFW_TRUE", "GLFW error", MB_OK);
	}

	// create window
	glfwWindowHint(GLFW_SAMPLES, 8);
	WindowManager::AddWindow("main", new Window(800, 800, "Logic Gate Simulator", WINDOWMODE::WINDOWED));
	WindowManager::GetWindow("main")->MakeContextCurrent();
	WindowManager::GetWindow("main")->SetVsync(1);
	ImGuiManager::Init();

	// init glew
	if (glewInit() != GLEW_OK)
	{
		running = false;
		MessageBoxA(0, "GLEWInit != GLEW_OK", "GLEW error", MB_OK);
	}

	// set input window
	WindowManager::GetWindow("main")->MakeContextCurrent();
	Input::AddWindow(WindowManager::GetWindow("main")->GetHandle());

	// load font
	FontRenderer::LoadFont("./fonts/smallFont/smallFont.fnt");

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// start loops
	new CircuitManager;
	std::thread logicThread(&Program::logicLoop, this);
	renderLoop();
	logicThread.join();
}

Program::~Program()
{
	for(auto& it : CircuitManager::managers)
		it.second->Exit();
	glfwSetErrorCallback(NULL);
	ImGuiManager::Exit();
	WindowManager::Terminate();
	glfwTerminate();
}

void Program::logicLoop()
{
	while (running)
	{
		auto timerStart = std::chrono::system_clock::now();

		// update circuits
		CircuitManager::managers[Settings::currentMapID]->Update();
		// update wires
		WireManager::Update();

		std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - timerStart);
		if(diff < std::chrono::milliseconds(10))
			std::this_thread::sleep_for(std::chrono::milliseconds(10) - diff);
	}
}

void Program::renderLoop()
{
	bool isAnyHovered = false;
	while (running)
	{
		// check if program should close
		if (glfwWindowShouldClose(WindowManager::GetWindow("main")->GetHandle()))
			running = false;

		// clear screen
		glClearColor(Settings::backgroundColor[0], Settings::backgroundColor[1], Settings::backgroundColor[2], 0);
		glClear(GL_COLOR_BUFFER_BIT);

		// input
		WireManager::ConnectNewLine();


		// menus
		if (!ImGuiManager::Update())
		{
			// navigation input
			if (!Input::GetMouseButton(WindowManager::GetWindow("main")->GetHandle(), Input::Mouse::LEFT, Input::Action::HOLD))
				isAnyHovered = CircuitManager::managers[Settings::currentMapID]->UpdateHovered();
			CoordinateSystem::UpdateCamera(isAnyHovered);
		}
		CircuitManager::managers[Settings::currentMapID]->UpdateHoveredIO();

		// render
		Renderer::Render();
		FontRenderer::RenderFont();
		ImGuiManager::Render();
		// swap buffers and poll input
		WindowManager::GetWindow("main")->Update();
		Input::Poll();
		glfwPollEvents();
	}
}
