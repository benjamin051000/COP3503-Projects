#pragma once
#include <iostream>
#include "Tile.h"
using namespace std;

class Graphics;

class Game {
	Graphics* gameWindow;

	/*Number of mines and number of tiles*/
	const int numMines = 50, numTiles = 400;

	/*Positions of the different menu options*/
	
	bool running = true;
	
	/*Minefield of Tile objects*/
	static const int rows = 16, cols = 25;
	Tile mineField[rows][cols];

	void gameLoop();
	
	/*"Digs" a tile up and reveals its state. Checks surrounding tiles to determine state.*/
	void Reveal(int r, int c);
	void GameOver();
	
public:
	/*Prints the board in the console. 1s are mines, 0s are blanks.*/
	void PrintBoard() const;

	/*Creates a game and starts it.*/
	Game();
	~Game();
	const int GetRows() const;
	const int GetCols() const;
	Tile getTile(int r, int c) const;

	/*Stops the gameLoop, terminating the game.*/
	void StopRunning();

	void NewGame();
};