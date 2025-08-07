#pragma once

#include <SFML/Graphics.hpp>
#include <array>

typedef sf::Vector2i position;
typedef sf::Vector2f vpos;

constexpr int cellSize = 4;

enum SubcellType { Path, Wall };

enum class Tracker {
	Visited, Blocked, None
};

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

	bool isStart;

	position Mparent;
	Tracker Mtracker;
	
public:
	Cell();

	void draw(sf::RenderWindow& window);

	bool contains(vpos screenpos);
	void changeColor();

	// setters
	void setPosition(position gridpos) { Position = gridpos; }
	void setScreenPos(position gridPos);
	void setMazeParent(position gridPos) { Mparent = gridPos; }
	void setMazeTracker(Tracker newTracker) { Mtracker = newTracker; }

	//getters
	position getPosition() { return Position; }
	position getMazeParent() { return Mparent; }
	Tracker getMazeTracker() { return Mtracker; }
	std::array<std::array<SubCell, cellSize>, cellSize>& getSubcells() { return cell; }
};

