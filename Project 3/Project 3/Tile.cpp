#include "Tile.h"

Tile::Tile(bool m) {
	mine = m;
	revealed = false;
	flagged = false;
}