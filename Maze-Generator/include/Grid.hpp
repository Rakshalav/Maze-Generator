#pragma once

#include "Cell.hpp"
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

constexpr int COL = 100;
constexpr int ROW = 50;

typedef std::vector<std::vector<Cell>> cells;

class Grid
{

public:
	Grid();
	static cells grid;

	void draw(sf::RenderWindow& window);
	~Grid();
};
