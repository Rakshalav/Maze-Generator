#pragma once

#include "Cell.h"
#include <SFML/Graphics.hpp>
#include <array>

constexpr int COL = 40;
constexpr int ROW = 25;

typedef std::array<std::array<Cell, ROW>, COL> cells;

class Grid
{
private:
	sf::RenderWindow* window;

	cells* grid = nullptr;

public:
	Grid(sf::RenderWindow& win);
	void draw();
	cells* getGrid() { return grid; }
	~Grid();
};

