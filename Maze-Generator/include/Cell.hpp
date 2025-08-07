#pragma once

#include <SFML/Graphics.hpp>
#include <array>

typedef sf::Vector2i position;
typedef sf::Vector2f vpos;

constexpr int cellSize = 4;

enum SubcellType { Path, Wall };

struct SubCell : public sf::RectangleShape
{
	SubCell();

	// variables
	position Cellpos;
	SubcellType type;
};

class Cell
{
private:
	position Position;
	std::array<std::array<SubCell, cellSize>, cellSize> cell;


public:
	Cell();

	void draw(sf::RenderWindow& window);

	bool contains(vpos screenpos);
	void changeColor();

	// setters
	void setPosition(position gridpos) { Position = gridpos; }
	void setScreenPos(position gridPos);


	//getters
	position getPosition() { return Position; }
	std::array<std::array<SubCell, cellSize>, cellSize>& getSubcells() { return cell; }
};

