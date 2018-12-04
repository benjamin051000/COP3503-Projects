#include "Tile.h"

Tile::Tile(int r, int c, std::vector<Tile*> adj) {
	this->r = r;
	this->c = c;
	adjacents = adj;
}
