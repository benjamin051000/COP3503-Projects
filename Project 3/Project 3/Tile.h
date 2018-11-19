#pragma once

struct Tile {
	bool mine, flagged, revealed;
	Tile(bool m = false);
};