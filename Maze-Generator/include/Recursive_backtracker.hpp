#pragma once

#include <stack>
#include "Grid.hpp"
#include <random>

class MazeGenerator
{
private:

	cells& grid;

	bool generationStarted = false;
	bool wantDelay = true;

	std::stack<position> Stack;
	bool visited[COL][ROW];

	bool isValid(position gridpos);
	position random(std::vector<position> validDirs);

	position previousTop = position(-1, -1);


public:
	MazeGenerator();

	static bool mazeDone;

	void init();
	void update();
	void generate();

	~MazeGenerator();
};