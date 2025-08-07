#pragma once

#include <stack>
#include "Grid.h"
#include <random>
#include <ranges>
#include <thread>

class MazeGenerator
{
private:
	Grid* grid;
	bool mazeDone = false;

	cells* gridPtr = nullptr;
	std::stack<position> Stack;
	bool visited[COL][ROW];

	bool isValid(position gridpos);
	position random(std::vector<position> validDirs);

public:
	MazeGenerator(Grid& grid_);

	void generateMaze();
};