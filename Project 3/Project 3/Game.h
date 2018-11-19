#pragma once
#include <iostream>
#include "Graphics.h"

using namespace std;

class Game {
	Graphics gameWindow;
	/*Number of mines and number of tiles*/
	const int numMines = 50, numTiles = 400;

	struct Tile {
		bool mine, flagged;
		Tile(bool m = false);
	};
	
	static const int rows = 16, cols = 25;
	Tile mineField[rows][cols];
public:
	void PrintBoard() const;
	Game();
};