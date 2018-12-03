#pragma once

struct Tile {
	bool mine, flagged, revealed, debug;
	Tile(bool m = false);
};