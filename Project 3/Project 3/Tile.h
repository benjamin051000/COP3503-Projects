#pragma once
#include <vector>

struct Tile {
	bool mine, flagged, revealed, debug;
	std::vector<Tile*> adjacents;
	Tile(std::vector<Tile*> adj);
	Tile() {}
};