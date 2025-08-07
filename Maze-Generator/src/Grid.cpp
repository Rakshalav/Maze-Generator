#include "../include/Grid.h"

Grid::Grid(sf::RenderWindow& win) : window(&win)
{
	grid = new cells;

	for (int x = 0; x < COL; x++) {
		for (int y = 0; y < ROW; y++) {
			position gridPos(x, y);
			auto& cell = (*grid)[x][y];
			cell.setPosition(gridPos);
			cell.setScreenPos(gridPos);
		}
	}
}

void Grid::draw()
{
	for (auto& col : *grid) {
		for (auto& cell : col) {
			cell.draw(*window);
		}
	}
}

Grid::~Grid() {
	delete[] grid;
	grid = nullptr;
}