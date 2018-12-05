#include "Tile.h"

Tile::Tile(short r, short c, std::vector<Tile*> adj) {
	row = r;
	col = c;
	adjacents = adj;
}