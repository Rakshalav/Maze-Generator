#include "../include/Recursive_backtracker.hpp"

MazeGenerator::MazeGenerator(Grid& grid_) : grid(&grid_)
{
	gridPtr = grid->getGrid();
	memset(visited, false, sizeof(visited));
}

bool MazeGenerator::isValid(position gridpos)
{
	if (gridpos.x >= 0 && gridpos.x < COL && gridpos.y >= 0 && gridpos.y < ROW)
		return true;
	return false;
}

position MazeGenerator::random(std::vector<position> validDirs)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::ranges::shuffle(validDirs, gen); 
	std::uniform_int_distribution<int> dist(0, static_cast<int>(validDirs.size()) - 1);
	int i = dist(gen); 

	return validDirs[i];
}


void MazeGenerator::generateMaze()
{
	auto& startingCell = (*gridPtr)[0][0];
	auto staringPos = startingCell.getPosition();
	Stack.push(staringPos);
	visited[staringPos.x][staringPos.y] = true;

	position dirs[4] = {
		{0, -1},  // North
		{1, 0},   // East
		{0, 1},   // South
		{-1, 0}   // West
	};

	while (!Stack.empty())
	{

		auto current = Stack.top();
		visited[current.x][current.y] = true;

		std::vector<position> validDirs;

		//check north neighbor
		auto neighborNorth = current + dirs[0];
		if (isValid(neighborNorth) && !visited[neighborNorth.x][neighborNorth.y])
			validDirs.push_back(neighborNorth);

		//check east neighbor
		auto neighborEast = current + dirs[1];
		if (isValid(neighborEast) && !visited[neighborEast.x][neighborEast.y])
			validDirs.push_back(neighborEast);

		//check South neighbor
		auto neighborSouth = current + dirs[2];
		if (isValid(neighborSouth) && !visited[neighborSouth.x][neighborSouth.y])
			validDirs.push_back(neighborSouth);

		//check West neighbor
		auto neighborWest = current + dirs[3];
		if (isValid(neighborWest) && !visited[neighborWest.x][neighborWest.y])
			validDirs.push_back(neighborWest);

		if (!validDirs.empty()) {
			auto next = random(validDirs);
			visited[next.x][next.y] = true;
			Stack.push(next);

			auto& cellCurrent = (*gridPtr)[current.x][current.y];
			auto& cellNext = (*gridPtr)[next.x][next.y];
			auto dir = next - current;

			auto& currentArray = cellCurrent.getSubcells();
			auto& nextArray = cellNext.getSubcells();

			// North
			if (dir == dirs[0]) {
				nextArray[0][3].type = Path;
				nextArray[1][3].type = Path;
				nextArray[2][3].type = Path;
				cellNext.changeColor();
			}
			// East
			else if (dir == dirs[1]) {
				currentArray[3][0].type = Path;
				currentArray[3][1].type = Path;
				currentArray[3][2].type = Path;
				cellCurrent.changeColor();
			}
			// South
			else if (dir == dirs[2]) {
				currentArray[0][3].type = Path;
				currentArray[1][3].type = Path;
				currentArray[2][3].type = Path;
				cellCurrent.changeColor();
			}
			// West
			else if (dir == dirs[3]) {
				nextArray[3][0].type = Path;
				nextArray[3][1].type = Path;
				nextArray[3][2].type = Path;
				cellNext.changeColor();
			}
		}
		else Stack.pop();
	}
}

MazeGenerator::~MazeGenerator()
{
	while (!Stack.empty())
		Stack.pop();

	
}