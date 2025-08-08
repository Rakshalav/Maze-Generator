#pragma once

#include "Cell.hpp"
#include <SFML/Graphics.hpp>
#include <array>

constexpr int COL = 45;
constexpr int ROW = 25;

typedef std::array<std::array<Cell, ROW>, COL> cells;

class Grid
{

public:
	Grid();
	static cells* grid;

	void draw(sf::RenderWindow& window);
	~Grid();
};
