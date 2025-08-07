#include "../include/Cell.h"

//--------------------(Sub-Cell)--------------------
SubCell::SubCell() 
{
	this->Cellpos = { 0, 0 };
	this->type = Path;
}

//--------------------(Cell)--------------------
Cell::Cell()
{
	{
		for (int x = 0; x < cellSize; x++) {
			for (int y = 0; y < cellSize; y++) {
				position cellpos = { x, y };
				cell[x][y].Cellpos = cellpos;
			}
		}

		/* 1  2  3  4
		   5  6  7  8	
		   9  10 11 12
		   13 14 15 16
		*/ 
		auto& subcell_4 = cell[3][0]; auto& subcell_8 = cell[3][1]; auto& subcell_12 = cell[3][2];
		auto& subcell_13 = cell[0][3];  auto& subcell_14 = cell[1][3]; auto& subcell_15 = cell[2][3];  auto& subcell_16 = cell[3][3];

		subcell_4.type = Wall; subcell_8.type = Wall; subcell_12.type = Wall;
		subcell_13.type = Wall; subcell_14.type = Wall; subcell_15.type = Wall; subcell_16.type = Wall;
	}
	
	this->isStart = false;
	this->Mtracker = Tracker::None;
	this->Mparent = { -1, -1 };
}


void Cell::setScreenPos(position gridPos)
{
	float subcellSize = 10.0f;
	float size = cellSize * subcellSize;
	for (int sx = 0; sx < cellSize; sx++) {
		for (int sy = 0; sy < cellSize; sy++) {
			float screenX = gridPos.x * size + sx * subcellSize;
			float screenY = gridPos.y * size + sy * subcellSize;

			auto& subcell = cell[sx][sy];

			subcell.setPosition({ screenX, screenY });
			subcell.setSize({ subcellSize, subcellSize });

			if (subcell.type == Path)
				subcell.setFillColor(sf::Color::White);
			else 
				subcell.setFillColor(sf::Color::Black);
		}
	}
}

void Cell::draw(sf::RenderWindow& window)
{
	for (auto& col : cell) {
		for (auto& subcell : col) {
			window.draw(subcell);
		}
	}
}

bool Cell::contains(vpos screenpos)
{
	for (auto& col : cell) {
		for (auto& subcell : col) {
			return subcell.getGlobalBounds().contains(screenpos);
		}
	}
}

void Cell::changeColor() 
{
	for (auto& col : cell) {
		for (auto& subcell : col) {
			if (subcell.type == Path)
				subcell.setFillColor(sf::Color::White);
		}
	}
}