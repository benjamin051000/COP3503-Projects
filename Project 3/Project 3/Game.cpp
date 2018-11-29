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
			
			/*Check buttons first*/
			
			/*Reveal tile*/
			if (position.x > 0 && position.y > 0) {
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
		
	}
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
	gameWindow = new Graphics(this); //can't create this on stack? ugh
	PrintBoard();
	gameLoop();
}