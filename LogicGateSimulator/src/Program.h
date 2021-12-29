#pragma once
#include <Windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Program
{
public:
	Program();
	~Program();
private:
	void logicLoop();
	void renderLoop();
private:
	bool running;
};