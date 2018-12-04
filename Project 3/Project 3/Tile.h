#pragma once
#include <vector>

struct Tile {
	/*The position of the Tile on mineField*/
	short row, col;

	/*Whether the tile has a mine, flag, or is revealed.*/
	bool mine = false, flagged = false, revealed = false;
	
	/*The number of adjacent mines to the tile, determined in game->Reveal()*/
	short nearbyMines = 0;

	/*Tile pointers to each adjacent tile, including this Tile.*/
	std::vector<Tile*> adjacents;

	/*Construction*/
	Tile(short r, short c, std::vector<Tile*> adj);
	Tile() {}
};