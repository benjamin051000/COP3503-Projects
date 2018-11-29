#include "Game.h"
#include "Graphics.h"

void Game::gameLoop() {
	gameWindow->update();

	while (running) {
		/*Check for a click*/

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			
			sf::Vector2i position = gameWindow->getMouseCoords();
			
			/*Wait until LMB is released*/
			while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {}
			
			/*Check menu buttons*/
			if (position.y > 16 * 32 && position.y < 16 * 32 + 64) { // do this better
				int c = 400 - 32; //starting pos of smiley face
				int x = position.x;
				if (x > c && x < c + 64) {
					/*Smiley*/
					cout << ":)" << endl;
					NewGame();
				}
				else if (x > c + 2 * 64 && x < c + 3 * 64) {
					/*Debug*/
					cout << "debug selected" << endl;
				}
				else if (x > c + 3 * 64 && x < c + 4 * 64) {
					/*test one*/
					cout << "test_1 selected" << endl;
				}
				else if (x > c + 4 * 64 && x < c + 5 * 64) {
					/*test two*/
					cout << "test_2 selected" << endl;
				}
			}


			if (position.x > 0 && position.y > 0) {

				/*Reveal tile*/
				int r = position.y / 32, c = position.x / 32;
				if (!mineField[r][c].flagged) {
					Reveal(r, c); //y is row, x is col
				}
			}

			/*Update graphics window.*/
			gameWindow->update();
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			
			sf::Vector2i position = gameWindow->getMouseCoords();

			/*Wait until RMB is released*/
			while (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {}

			/*Toggle flag*/
			if (position.x > 0 && position.y > 0) {
				int r = position.y / 32, c = position.x / 32;
				if (!mineField[r][c].revealed) {
					mineField[r][c].flagged = !mineField[r][c].flagged;
				}
			}

			/*Update graphics window.*/
			gameWindow->update();
		}

	} //end of while
}

void Game::Reveal(int r, int c) {
	mineField[r][c].revealed = true;

	if (mineField[r][c].mine) {
		GameOver();
	}
}

void Game::GameOver() {
	cout << "Game over!" << endl;
	for (auto& row : mineField) {
		for (Tile& tile : row) {
			if (tile.mine && !tile.flagged) {
				tile.revealed = true;
			}
		}
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
	NewGame();
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
	return mineField[r][c];
}

void Game::StopRunning() {
	running = false;
}

void Game::NewGame() {
	cout << "New game created." << endl;

	/*reset minefield*/
	layMines();

	PrintBoard();
	gameLoop();
}

void Game::layMines() {
	for (auto &cols : mineField) {
		for (auto &tile : cols) {
			tile.flagged = false;
			tile.revealed = false;
			tile.mine = true; //do this randomly
		}
	}
}
