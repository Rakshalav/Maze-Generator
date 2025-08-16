#pragma once

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

#include "../include/Grid.hpp"
#include "../include/Astar.hpp"
#include "../include/Recursive_backtracker.hpp"

class Application
{
private:
	sf::RenderWindow window;
	sf::Vector2f window_size;
	sf::View view;

	float Gui_margin;
	sf::Event event;
	sf::Clock deltaClock;

	Grid grid;
	MazeGenerator mazeGenerator;
	Astar aStar;

	bool dragging = false;
	sf::Vector2f lastMousePos;
	sf::Vector2f getMousePos();

public:
	Application();

	void run();
	void render();
	void renderImGui();
	void eventHandler(float dt);
};
