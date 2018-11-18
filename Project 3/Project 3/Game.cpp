#include "Game.h"

void Game::PrintBoard() const {
	int i = 1;
	for (auto& row : mineField) {
		for (auto& tile : row) {
			cout << (tile.isMine ? "1" : "0");
			if (i % cols == 0) {
				cout << endl;
			}
			i++;
		}
	}
}

Game::Game() {

}

Game::Mine::Mine(bool m) {
	isMine = m;
}
