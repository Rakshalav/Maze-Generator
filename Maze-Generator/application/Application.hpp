#pragma once

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

#include "Grid.hpp"
#include "Recursive_backtracker.hpp"

class Application
{
private:
	sf::RenderWindow window;
	sf::Vector2f window_size;
	sf::RectangleShape displayArea;
	float Gui_margin;
	sf::Event event;

	Grid grid;
	MazeGenerator mazeGenerator;

public:
	Application();

	void run();
	void render();
	void renderImGui();
	void eventHandler();
};