#pragma once
#include <iostream>
#include <random>
#include "Tile.h"
using namespace std;

class Graphics;

class Game {
	/*Connects the graphics window to the game logic.*/
	Graphics* gameWindow;

	/*Number of mines and number of tiles*/
	const short numMines = 50, numTiles = 400;

	/*Toggles off  if the window X button is 
	pressed on the window, to stop the program.*/
	bool running = true;
	
	/*Minefield of Tile objects*/
	static const short rows = 16, cols = 25;
	Tile mineField[rows][cols];

	/*Used in GetMinesLeft to quickly determine which
	mines have been flagged.*/
	vector<Tile*> vecOfMinePtrs;

	/*Main loop of the program. Listens for a 
	click, then updates the graphics window.*/
	void gameLoop();
	
	/*"Digs" a tile up and reveals its state. 
	Checks surrounding tiles to determine state.*/
	void Reveal(short r, short c);

	/*Runs when a mine is clicked. Stops the game and prevents 
	further interaction until the smiley is clicked.*/
	void GameOver();

	/*Take the coordinates of a left and right click,
	and trigger the appropriate response.*/
	void ProcessLeftClick();
	void ProcessRightClick();
	
	/*Adds numMines random mines in mineField*/
	void LayMines();

	/*Clears all flags, mines, and revealed tiles.
	Initializes Adjacent Tile pointers.*/
	void ResetBoard();

	/*Creates a new version of the game.*/
	void NewGame();

public:
	/*Used for drawing the mines and printing out stuff
	if enabled.*/
	bool debug = false;

	/*Used for drawing the sad face, as well as preventing 
	further tile reveals after a mine is revealed.*/
	bool gameover = false;

	/*Prints the board in the console. 1s are mines, 0s are blanks.*/
	void PrintBoard() const;

	/*Creates a game and starts it.*/
	Game();
	~Game();
	
	/*Returns the number of rows in mineField*/
	const int GetRows() const;
	
	/*Returns the number of columns in mineField*/
	const int GetCols() const;
	
	/*Returns a Tile (used for graphics drawing)*/
	Tile getTile(int r, int c) const;

	/*Stops gameLoop, terminating the program.*/
	void StopRunning();

	/*Used for win condition and drawing of 
	minesLeft numbers in bottom left corner.*/
	unsigned short GetMinesLeft() const;

	/*Checks if the win condition is met:
	All non-mine tiles must be revealed.*/
	bool WinCondition();
};