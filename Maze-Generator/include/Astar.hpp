#pragma once

#include "Grid.hpp"
#include "Cell.hpp"
#include "Recursive_backtracker.hpp"

#include <set>
#include <utility>
#include <iostream>

typedef std::pair<int, sf::Vector2i> Pair;

struct Compare {
	bool operator()(const Pair& a, const Pair& b) const {
		const auto& Fa = std::get<0>(a);
		const auto& posA = std::get<1>(a);
		const auto& Fb = std::get<0>(b);
		const auto& posB = std::get<1>(b);

		if (Fa != Fb)
			return Fa < Fb; 

		if (posA.x != posB.x)
			return posA.x < posB.x;
		return posA.y < posB.y;
	}
};

class Astar
{
private:
	cells* gridPtr = nullptr;
	std::set<Pair, Compare> openList;
	bool closedList[COL][ROW];

	bool startAstar = false;
	bool wantDelay = true;

	// helper functions
	//bool areEmpty();
	bool isValid(position position);
	bool isUnblocked(position parent, position child);
	bool isDestination(position parent);
	int calculateHval(position currentPos);

public:
	Astar();
	bool foundDest;
	void init();
	void tracePath();
	void pathFind();
	void update();
};