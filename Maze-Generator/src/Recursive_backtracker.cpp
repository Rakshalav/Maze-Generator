#include "../include/Recursive_backtracker.hpp"

bool MazeGenerator::mazeDone = false;

MazeGenerator::MazeGenerator() : grid(Grid::grid)
{
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

void MazeGenerator::init()
{
	auto& startingCell = grid[0][0];
    startingCell.setState(CellState::Start);
	auto staringPos = startingCell.getPosition();
	Stack.push(staringPos);
	visited[staringPos.x][staringPos.y] = true;

	generationStarted = true;
}

void MazeGenerator::generate()
{
    if (wantDelay)
        return;

    if (!generationStarted) {
        mazeDone = true;
        return;
    }

    while (!Stack.empty())
    {
        update();
    }
}

void MazeGenerator::update()
{
    if (!generationStarted || Stack.empty()) {
        mazeDone = true;
        return;
    }

    if (previousTop != position(-1, -1)) {
        auto& prevCell = grid[previousTop.x][previousTop.y];
        auto& prevSubCells = prevCell.getSubcells();

        prevSubCells[0][0].setFillColor(sf::Color::White); prevSubCells[1][0].setFillColor(sf::Color::White); prevSubCells[2][0].setFillColor(sf::Color::White);
        prevSubCells[0][1].setFillColor(sf::Color::White); prevSubCells[1][1].setFillColor(sf::Color::White); prevSubCells[2][1].setFillColor(sf::Color::White);
        prevSubCells[0][2].setFillColor(sf::Color::White); prevSubCells[1][2].setFillColor(sf::Color::White); prevSubCells[2][2].setFillColor(sf::Color::White);
    }

    position dirs[4] = {
        {0, -1},  // North
        {1, 0},   // East
        {0, 1},   // South
        {-1, 0}   // West
    };

    auto current = Stack.top();
    visited[current.x][current.y] = true;

    // Mark current top cell green
    auto& topCell = grid[current.x][current.y];
    auto& topSubCell = topCell.getSubcells();

    topSubCell[0][0].setFillColor(sf::Color::Green); topSubCell[1][0].setFillColor(sf::Color::Green); topSubCell[2][0].setFillColor(sf::Color::Green);
    topSubCell[0][1].setFillColor(sf::Color::Green); topSubCell[1][1].setFillColor(sf::Color::Green); topSubCell[2][1].setFillColor(sf::Color::Green);
    topSubCell[0][2].setFillColor(sf::Color::Green); topSubCell[1][2].setFillColor(sf::Color::Green); topSubCell[2][2].setFillColor(sf::Color::Green);

    previousTop = current; 

    std::vector<position> validDirs;

    // Check each direction
    auto neighborNorth = current + dirs[0];
    if (isValid(neighborNorth) && !visited[neighborNorth.x][neighborNorth.y])
        validDirs.push_back(neighborNorth);

    auto neighborEast = current + dirs[1];
    if (isValid(neighborEast) && !visited[neighborEast.x][neighborEast.y])
        validDirs.push_back(neighborEast);

    auto neighborSouth = current + dirs[2];
    if (isValid(neighborSouth) && !visited[neighborSouth.x][neighborSouth.y])
        validDirs.push_back(neighborSouth);

    auto neighborWest = current + dirs[3];
    if (isValid(neighborWest) && !visited[neighborWest.x][neighborWest.y])
        validDirs.push_back(neighborWest);

    if (!validDirs.empty()) {
        auto next = random(validDirs);
        visited[next.x][next.y] = true;
        Stack.push(next);

        auto dir = next - current;
        auto& nextCell = grid[next.x][next.y];
        nextCell.setMazeParent(current);

        auto& currentArray = topCell.getSubcells();
        auto& nextArray = nextCell.getSubcells();

        // Carve path depending on direction
        if (dir == dirs[0]) { // North
            nextArray[0][3].type = Path;
            nextArray[1][3].type = Path;
            nextArray[2][3].type = Path;
            nextCell.changeColor();
        }
        else if (dir == dirs[1]) { // East
            currentArray[3][0].type = Path;
            currentArray[3][1].type = Path;
            currentArray[3][2].type = Path;
            topCell.changeColor();
        }
        else if (dir == dirs[2]) { // South
            currentArray[0][3].type = Path;
            currentArray[1][3].type = Path;
            currentArray[2][3].type = Path;
            topCell.changeColor();
        }
        else if (dir == dirs[3]) { // West
            nextArray[3][0].type = Path;
            nextArray[3][1].type = Path;
            nextArray[3][2].type = Path;
            nextCell.changeColor();
        }
    }
    else {
        Stack.pop();
    }
}


MazeGenerator::~MazeGenerator()
{
    std::stack<position> emptyStk;
    Stack.swap(emptyStk);
}