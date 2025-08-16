#include "../include/Astar.hpp"

Astar::Astar() : grid(Grid::grid)
{
    memset(closedList, false, sizeof(closedList));
    foundDest = false;
}

bool Astar::isValid(position position) 
{
	if (position.x >= 0 && position.x < COL && position.y >= 0 && position.y < ROW)
		return true;
	return false;
}

bool Astar::isUnblocked(position parent, position child)
{
    position direction = child - parent;

    auto& cellParent = grid[parent.x][parent.y];
    auto& subcellsParent = cellParent.getSubcells();

    auto& cellChild = grid[child.x][child.y];
    auto& subcellChild = cellChild.getSubcells();
    
    if (direction == position(0, -1)) { //North
        if (subcellChild[0][3].type == Wall && subcellChild[1][3].type == Wall && subcellChild[2][3].type == Wall)
            return false;
    }
    else if (direction == position(1, 0)) { // East
        if (subcellsParent[3][0].type == Wall && subcellsParent[3][1].type == Wall && subcellsParent[3][2].type == Wall)
            return false;
    }
    else if (direction == position(0, 1)) { // South
        if (subcellsParent[0][3].type == Wall && subcellsParent[1][3].type == Wall && subcellsParent[2][3].type == Wall)
            return false;
    }
    else if (direction == position(-1, 0)) { // West
        if (subcellChild[3][0].type == Wall && subcellChild[3][1].type == Wall && subcellChild[3][2].type == Wall)
            return false;
    }
    
    return true;
}

bool Astar::isDestination(position position)
{
	return grid[position.x][position.y].getState() == CellState::Target;
}

int Astar::calculateHval(position currentPos) 
{
	position goal(-1, -1);

	for (auto& col : grid) {
		for (auto& cell : col) {
			if (cell.getState() == CellState::Target) {
				goal = cell.getPosition();
				break;
			}
		}
		if (goal.x != -1) break;
	}

	int h = std::abs(currentPos.x - goal.x) + std::abs(currentPos.y - goal.y);

	return h;
}

void Astar::tracePath() 
{
    bool foundTarget = false;
    position targetPos;

    for (auto& col : grid) {
        for (auto& node : col) {
            if (node.getState() == CellState::Target) {
                targetPos = node.getPosition();
                foundTarget = true;
                break;
            }
        }
        if (foundTarget)
            break;
    }

    position current = targetPos;
    while (true) {
        auto& cell = grid[current.x][current.y];

        if (cell.getState() != CellState::Start && cell.getState() != CellState::Target) {
            cell.setState(CellState::Path);
            auto& cellArray = cell.getSubcells();

            for (auto& col : cellArray) {
                for (auto& subcell : col) {
                    if (subcell.type == Path)
                        subcell.setFillColor(sf::Color::Yellow);
                }
            }
        }

        position parent = cell.getParent();
        if (parent == position(-1, -1)) break;
        if (grid[parent.x][parent.y].getState() == CellState::Start)
            break;

        current = parent;
    }
}

void Astar::init() 
{

    if (foundDest)
        foundDest = false;

    Cell* startCell = nullptr;
    for (auto& col : grid) {
        for (auto& cell : col) {
            auto state = cell.getState();
            if (state == CellState::Start) {
                startCell = &cell;
                break;
            }
        }
        if (startCell) break;
    }

    startCell->setFcost(0);
    startCell->setGcost(0);
    startCell->setHcost(0);
    int f_Start = startCell->getFcost();
    position gridPos_Start = startCell->getPosition();
    Pair Source = std::make_pair(f_Start, gridPos_Start);
    openList.insert(Source);

    position targetCellpos(COL - 1, ROW - 1);
    auto& Targetcell = grid[targetCellpos.x][targetCellpos.y];
    Targetcell.setState(CellState::Target);
    auto& subcellstarget = Targetcell.getSubcells();
    subcellstarget[0][0].setFillColor(sf::Color::Red); subcellstarget[1][0].setFillColor(sf::Color::Red); subcellstarget[2][0].setFillColor(sf::Color::Red);
    subcellstarget[0][1].setFillColor(sf::Color::Red); subcellstarget[1][1].setFillColor(sf::Color::Red); subcellstarget[2][1].setFillColor(sf::Color::Red);
    subcellstarget[0][2].setFillColor(sf::Color::Red); subcellstarget[1][2].setFillColor(sf::Color::Red); subcellstarget[2][2].setFillColor(sf::Color::Red);

    if (startCell != nullptr) 
        startAstar = true;

    if (startAstar && !wantDelay)
        pathFind();
}

void Astar::pathFind()
{
    while (!openList.empty())
    {   
        update();
        if (foundDest)
            break;
    }
}

void Astar::update()
{
    if (!startAstar)
        return;

    if (openList.empty()) {
        foundDest = true;
        return;
    }

    auto current = *openList.begin();
    openList.erase(openList.begin());
    auto& pos = std::get<1>(current);
    closedList[pos.x][pos.y] = true;

    int fnew, gnew, hnew;

    std::vector<position> directions = {
        {0 + pos.x, -1 + pos.y },  // North
        {1 + pos.x, 0 + pos.y },   // East
        {0 + pos.x, 1 + pos.y },   // South
        {-1 + pos.x, 0 + pos.y }   // West
    };

    for (auto& direction : directions) {
        if (isValid(direction)) {
            auto& cell = grid[direction.x][direction.y];
            if (isDestination(direction)) {
                cell.setParent(pos);
                tracePath();
                foundDest = true;
                return;
            }
            else if (!closedList[direction.x][direction.y] && isUnblocked(pos, direction)) {
                gnew = grid[pos.x][pos.y].getGcost() + 1;
                hnew = calculateHval(direction);
                fnew = gnew + hnew;

                if (cell.getFcost() == std::numeric_limits<int>::max() || cell.getFcost() > fnew) {
                    openList.emplace(std::make_pair(fnew, direction));
                    cell.setParent(pos);
                    cell.setGcost(gnew);
                    cell.setHcost(hnew);
                    cell.setFcost(fnew);
                    cell.setState(CellState::Visited);
                    auto& subcells = cell.getSubcells();
                    for (auto& col : subcells) {
                        for (auto& subcell : col) {
                            if (subcell.type == Path)
                                subcell.setFillColor(sf::Color(139, 208, 250));
                        }
                    }
                }
            }
        }
    }
}

Astar::~Astar()
{
    openList.clear();
}