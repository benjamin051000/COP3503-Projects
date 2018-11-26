#include "Game.h"
#include "Graphics.h"

void Game::gameLoop() {
	while (running) {
		/*Check for a click*/
		sf::Event mouseEvent;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			/*Get tile clicked*/
			sf::Vector2i position = gameWindow->getMouseCoords();

			/*Reveal tile*/
			int minePixelNum = 32;
			Reveal(position.y / minePixelNum, position.x / minePixelNum); //y is row, x is col
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			sf::Vector2i position = gameWindow->getMouseCoords();
			mineField[position.y / 32][position.x / 32].flagged = true;
		}

		/*Update graphics window.*/
		gameWindow->update();
	}
}

void Game::Reveal(int r, int c) {
	cout << r << '\t' << c << endl;
	mineField[r][c].revealed = true;

	if (mineField[r][c].mine) {
		cout << "Game over!" << endl;
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
	PrintBoard();
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
	return mineField[r][c];
}

void Game::StopRunning() {
	running = false;
}
