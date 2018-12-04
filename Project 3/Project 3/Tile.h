#pragma once
#include <vector>

struct Tile {
	bool mine = false, flagged = false, revealed = false, debug = false;
	short nearbyMines = 0;
	std::vector<Tile*> adjacents;
	Tile(std::vector<Tile*> adj);
	Tile() {}
};