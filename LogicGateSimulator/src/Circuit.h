#pragma once
#include <vector>
#include <string>
class Circuit
{
public:
	Circuit(int inputs, int outputs, std::string name);
	~Circuit();
	bool IsHovered();
	bool IsHoveredIO();
	void RenderBox();
	void RenderOutline();
	void RenderIO();
	void RenderFont();
	int posX, posY;
	struct IO
	{
		bool value = false;
		bool type;
		int posX, posY;
	};
	std::vector<IO> input;
	std::vector<IO> output;
	int width, height;
	float color[3];
	std::string name;

	static Circuit* hovered;
	static IO* hoveredIO;
private:
	int oldMX, oldMY;
};