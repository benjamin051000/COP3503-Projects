#include "Game.h"
#include "Graphics.h"

void Game::gameLoop() {
	while (gameWindow->gameLoop()) { //this is a terrible idea and is wrong. or maybe not (?)
		cout << "yee";
		/*TODO Game logic, intertwined with graphics*/
	}
}

void Game::PrintBoard() const {
	int i = 1;
	for (auto& row : mineField) {
		for (auto& tile : row) {
			cout << (tile.mine ? "1" : "0");
			if (i % cols == 0) {
				cout << endl;
			}
			i++;
		}
	}
}

Game::Game() {
	gameWindow = new Graphics(this); //can't create this on stack? ugh
	gameLoop();
}

Game::~Game() {
	delete gameWindow;
}

const int Game::GetRows() const {
	return rows;
}

const int Game::GetCols() const {
	return cols;
}

Tile Game::getTile(int r, int c) const {
	return mineField[r, c];
}
