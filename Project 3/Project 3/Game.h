#pragma once
#include <iostream>
#include "Tile.h"
using namespace std;

class Graphics;

class Game {
	Graphics* gameWindow;

	/*Number of mines and number of tiles*/
	const int numMines = 50, numTiles = 400;

	bool gameRunning = true;
	
	/*Minefield of Tile objects*/
	static const int rows = 16, cols = 25;
	Tile mineField[rows][cols];

	void gameLoop();

public:
	/*Prints the board in the console. 1s are mines, 0s are blanks.*/
	void PrintBoard() const;

	/*Creates a game and starts it.*/
	Game();
	~Game();
	const int GetRows() const;
	const int GetCols() const;
	Tile getTile(int r, int c) const;
};