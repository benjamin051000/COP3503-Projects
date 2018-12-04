#include "Game.h"
#include "Graphics.h"

void Game::gameLoop() {
	gameWindow->update();

	while (running) {
		/*Check for a click*/

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			
			ProcessLeftClick();

			/*Update graphics window.*/
			gameWindow->update();
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			
			ProcessRightClick();

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
	gameover = true;
	cout << "Game over!" << endl;
	for (auto& row : mineField) {
		for (Tile& tile : row) {
			if (tile.mine && !tile.flagged) {
				tile.revealed = true;
			}
		}
	}
}

void Game::ProcessLeftClick() {
	
	sf::Vector2i position = gameWindow->getMouseCoords();


	/*Wait until LMB is released*/
	while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {}

	if (position.x > 0 && position.y > 0) {
		/*Check menu buttons*/
		
		/*Smiley face*/
		sf::Vector2i smileyTL(gameWindow->faceCoords),
			smileyBR(gameWindow->faceCoords);
		smileyBR += sf::Vector2i(64, 64);

		if (position.x > smileyTL.x && position.x < smileyBR.x
			&& position.y > smileyTL.y && position.y < smileyBR.y) {
			cout << "Face clicked!" << endl;
			NewGame();
		}

		/*Debug button*/
		sf::Vector2i debugTL(gameWindow->debugCoords),
			debugBR(gameWindow->debugCoords);
		debugBR += sf::Vector2i(64, 64);

		if (position.x > debugTL.x && position.x < debugBR.x
			&& position.y > debugTL.y && position.y < debugBR.y) {
			cout << "Debug button clicked!" << endl;
			ToggleDebug();
		}




		if (gameover) { return; }

		/*Reveal tile*/
		int r = position.y / 32, c = position.x / 32;
		if (!mineField[r][c].flagged) {
			Reveal(r, c); //y is row, x is col
		}
	}
}

void Game::ProcessRightClick() {
	sf::Vector2i position = gameWindow->getMouseCoords();

	/*Wait until RMB is released*/
	while (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {}

	
	if (position.x > 0 && position.y > 0) {
		if (gameover) { return; }

		/*Toggle flag*/
		int r = position.y / 32, c = position.x / 32;
		if (!mineField[r][c].revealed) {
			mineField[r][c].flagged = !mineField[r][c].flagged;
		}
	}
}

void Game::LayMines() {
	int minesPlaced = 0;
	
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution<int> randRow(0, rows);
	uniform_int_distribution<int> randCol(0, cols);

	while(minesPlaced < numMines) {
			/*Pick a random location. If no mine, place one.
			If there is a mine, move to a different place.*/

		int r = randRow(rng);
		int c = randCol(rng);
		

		if (!mineField[r][c].mine) {
			mineField[r][c].mine = true;
			minesPlaced++;
			cout << "Placed mine " << minesPlaced << endl;
		}
	}
}

void Game::ResetBoard() {
	gameover = false;

	/*For each tile in mineField...*/
	for (auto &row : mineField) {
		for (auto &tile : row) {
			
			/*Create a vector of adjacent Tile pointers
			to pass to the Tile (used for revealing
			neighboring Tiles).*/
			vector<Tile*> adj;
			for (int r = -1; r <= 1; r++) {
				for (int c = -1; c <= 1; c++) {
					try {
						adj.push_back(&mineField[r][c]);
					}
					catch (exception) {
						adj.push_back(nullptr); //necessary? It might do this without throwing
					}
				}
			}

			tile = Tile(adj);

		}
	}

	
}

void Game::ToggleDebug() {
	for (auto &row : mineField) {
		for (auto &tile : row) {
			tile.debug = !tile.debug;
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
	ResetBoard();
	LayMines();

	PrintBoard();
	gameLoop();
}