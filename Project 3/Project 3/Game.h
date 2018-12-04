#pragma once
#include <iostream>
#include <random>
#include "Tile.h"
using namespace std;

class Graphics;

class Game {
	Graphics* gameWindow;

	/*Number of mines and number of tiles*/
	const int numMines = 50, numTiles = 400;

	bool running = true;
	
	/*Minefield of Tile objects*/
	static const int rows = 16, cols = 25;
	Tile mineField[rows][cols];

	void gameLoop();
	
	/*"Digs" a tile up and reveals its state. Checks surrounding tiles to determine state.*/
	void Reveal(int r, int c);
	void GameOver();

	/*Take the coordinates of a left and right click, and trigger the appropriate response.*/
	void ProcessLeftClick();
	void ProcessRightClick();
	
	/*Lays 50 random mines*/
	void LayMines();

	/*Clears all flags, mines, and revealed tiles.
	Initializes Adjacent Tile pointers.*/
	void ResetBoard();

	/*Toggles showing the mines*/
	void ToggleDebug();

public:
	/*Used for drawing the sad face, as well as preventing further tile reveals
	after a mine is revealed.*/
	bool gameover = false;

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