#pragma once

#include <stack>
#include "Grid.hpp"
#include <random>
#include <ranges>
#include <thread>
#include <chrono>

class MazeGenerator
{
private:

	cells* gridPtr = nullptr;
	bool mazeDone = false;
	bool generationStarted = false;
	std::stack<position> Stack;
	bool visited[COL][ROW];

	bool isValid(position gridpos);
	position random(std::vector<position> validDirs);

	position previousTop = position(-1, -1);


public:
	MazeGenerator();
	~MazeGenerator();

	void init();
	void update();
};