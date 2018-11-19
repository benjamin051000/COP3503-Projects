#include "Game.h"

void Game::gameLoop() {
	while (gameWindow.gameLoop()) {
		//cout << "Running..." << endl;
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
	gameLoop();
}

Game::Tile::Tile(bool m) {
	mine = m;
}
