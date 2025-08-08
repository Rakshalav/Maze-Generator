#include "../include/Grid.hpp"

cells* Grid::grid = nullptr;

Grid::Grid()
{
	Grid::grid = new cells;

	for (int x = 0; x < COL; x++) {
		for (int y = 0; y < ROW; y++) {
			position gridPos(x, y);
			auto& cell = (*grid)[x][y];
			cell.setPosition(gridPos);
			cell.setScreenPos(gridPos);
		}
	}
}

void Grid::draw(sf::RenderWindow& window)
{
	for (auto& col : *grid) {
		for (auto& cell : col) {
			cell.draw(window);
		}
	}
}

Grid::~Grid() {
	delete[] grid;
	grid = nullptr;
}