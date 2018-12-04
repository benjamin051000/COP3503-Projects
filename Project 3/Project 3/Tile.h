#pragma once
#include <vector>

struct Tile {
	int r, c;
	bool mine = false, flagged = false, revealed = false, debug = false;
	short nearbyMines = 0;
	std::vector<Tile*> adjacents;
	Tile(int r, int c, std::vector<Tile*> adj);
	Tile() {}
};