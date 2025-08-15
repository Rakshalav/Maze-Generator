#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <limits>

typedef sf::Vector2i position;
typedef sf::Vector2f vpos;

constexpr int cellSize = 4;

enum SubcellType { Path, Wall };

enum class CellState {
	None, Start, Target, Path, Visited, Blocked
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

	position mParent;

	CellState state;
	position pParent;

	int G = std::numeric_limits<int>::max();
	int H = std::numeric_limits<int>::max();
	int F = std::numeric_limits<int>::max();

public:
	Cell();

	void draw(sf::RenderWindow& window);

	bool contains(vpos screenpos);
	void changeColor();

	// setters
	void setPosition(position gridpos) { Position = gridpos; }
	void setScreenPos(position gridPos);
	void setMazeParent(position gridPos) { mParent = gridPos; }
	void setState(CellState newState) { state = newState; }
	void setParent(position newParent) { pParent = newParent; }
	void setFcost(int f) { F = f; }
	void setGcost(int g) { G = g; }
	void setHcost(int h) { H = h; }

	//getters
	const position& getPosition() const { return Position; }
	std::array<std::array<SubCell, cellSize>, cellSize>& getSubcells() { return cell; }
	const position& getMazeParent() const { return mParent; }
	const CellState& getState() const { return state; }
	const position& getParent() const { return pParent; }
	const int& getFcost() const { return F; }
	const int& getGcost() const { return G; }
	const int& getHcost() const { return H; }
};

