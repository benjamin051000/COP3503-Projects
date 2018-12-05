#include "Game.h"
#include "Graphics.h"

void Game::gameLoop() {
	gameWindow->update();

	while (running) {
		/*Check for a click*/

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			
			ProcessLeftClick();
			gameWindow->update();
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			
			ProcessRightClick();
			gameWindow->update();
		}
	}
}

void Game::Reveal(short r, short c) {
	mineField[r][c].revealed = true;

	if (mineField[r][c].mine) {
		GameOver();
	}
	else {

		/*How many surrounding Tiles are mines?*/
		short mineCount = 0;
		for (Tile* t : mineField[r][c].adjacents) {
			if (t->mine) { //throws
				mineCount++;
			}
		}

		cout << "Adjacent mines: " << mineCount << endl;
		mineField[r][c].nearbyMines = mineCount;

		/*Recursively check each adjacent tile, too.*/
		if (mineField[r][c].nearbyMines == 0) {
			for (Tile* t : mineField[r][c].adjacents) {
				if(!t->revealed)
					Reveal(t->row, t->col);
			}
		}

		WinCondition();
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

	if (position.x > 0 && position.y > 0 && position.x < 800 && position.y < 600) { //any way to extract W and H from Graphics?
		/*Check menu buttons*/
		
		/*Smiley face*/
		sf::Vector2i smileyTL(gameWindow->faceCoords),
			smileyBR(gameWindow->faceCoords);
		smileyBR += sf::Vector2i(64, 64);

		if (position.x > smileyTL.x && position.x < smileyBR.x
			&& position.y > smileyTL.y && position.y < smileyBR.y) {
			cout << "Face clicked!" << endl;
			NewGame();
			return;
		}

		/*Test_1*/
		sf::Vector2i test1TL(gameWindow->test1Coords),
				test1BR(gameWindow->test1Coords);
		test1BR += sf::Vector2i(64, 64);

		if (position.x > test1TL.x && position.x < test1BR.x
			&& position.y > test1TL.y && position.y < test1BR.y) {
			cout << "Test_1 clicked!" << endl;
			LoadFromFile("boards\\testboard.brd");
			return;
		}

		/*Test_2*/
		sf::Vector2i test2TL(gameWindow->test2Coords),
			test2BR(gameWindow->test2Coords);
		test2BR += sf::Vector2i(64, 64);

		if (position.x > test2TL.x && position.x < test2BR.x
			&& position.y > test2TL.y && position.y < test2BR.y) {
			cout << "Test_2 clicked!" << endl;
			LoadFromFile("boards\\testboard2.brd");
			return;
		}

		/*Guards against anything except
		the above buttons to be pressed
		when the game is over (win or loss).*/
		if (gameover) { return; }
		
		/*Debug button*/
		sf::Vector2i debugTL(gameWindow->debugCoords),
			debugBR(gameWindow->debugCoords);
		debugBR += sf::Vector2i(64, 64);

		if (position.x > debugTL.x && position.x < debugBR.x
			&& position.y > debugTL.y && position.y < debugBR.y) {
			cout << "Debug button clicked!" << endl;
			debug = !debug;
			return;
		}
		
		/*Reveal tile*/
		if (position.y < rows * 32) {
			int r = position.y / 32, c = position.x / 32;
			if (!mineField[r][c].flagged) {
				Reveal(r, c); //y is row, x is col
			}
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
	short minesPlaced = 0;
	
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution<int> randRow(0, rows);
	uniform_int_distribution<int> randCol(0, cols);

	while(minesPlaced < numMines) {
			/*Pick a random location. If no mine, place one.
			If there is a mine, move to a different place.*/

		short r = randRow(rng);
		short c = randCol(rng);
		

		if (!mineField[r][c].mine) {
			mineField[r][c].mine = true;
			minesPlaced++;
			vecOfMinePtrs.push_back(&mineField[r][c]);

			cout << "Placed mine " << minesPlaced << endl;
		}
	}
}

void Game::ResetBoard() {
	gameover = false;

	vecOfMinePtrs.clear();

	/*For each tile in mineField...*/
	for (int r = 0; r < /*sizeof(mineField) / sizeof(mineField[0])*/ rows; r++) {
		for (int c = 0; c < /*sizeof(mineField[0]) / sizeof(mineField[0][0])*/ cols; c++) {
			
			/*Create a vector of adjacent Tile pointers
			to pass to the Tile (used for revealing
			neighboring Tiles).*/
			vector<Tile*> adj;
			for (int adjr = -1; adjr <= 1; adjr++) {
				for (int adjc = -1; adjc <= 1; adjc++) {

					int ar = r + adjr, ac = c + adjc;

					/*Don't include nullptrs*/
					if (ar >= 0 && ar < rows && ac >= 0 && ac < cols) {
						adj.push_back(&mineField[ar][ac]);
					}

				}
			}

			/*Resets all other tile attributes*/
			mineField[r][c] = Tile(r, c, adj);
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

unsigned short Game::GetMinesLeft() const {
	short minesLeft = vecOfMinePtrs.size();

	for (Tile* tile : vecOfMinePtrs) {
		if (tile->flagged) {
			minesLeft--;
		}
	}
	return minesLeft;
}

bool Game::WinCondition() {
	for (auto & row : mineField) {
		for (auto & tile : row) {
			if (!tile.mine && !tile.revealed) {
				return false;
			}
		}
	}
	/*YOU WON!!!*/
	for (auto & row : mineField) {
		for (auto & tile : row) {
			if (tile.mine) {
				tile.flagged = true;
				GameOver();
			}
		}
	}
	return true;
}

void Game::NewGame() {
	ResetBoard();
	LayMines();

	PrintBoard();
	gameLoop();
}

void Game::LoadFromFile(string filename) {
	ResetBoard();

	ifstream file;
	file.open(filename);

	if (!file.is_open()) {
		cout << "Failed to open " << filename << endl;
	}

	/*These are coincidentally the same length*/
	string line;
	char minesFromFile[cols];
	int row = 0;

	while (getline(file, line, '\n')) {
		for (int i = 0; i < line.length(); i++) {
			minesFromFile[i] = line.at(i);
		}

		for (int col = 0; col < cols; col++) {
			if (minesFromFile[col] == '1') {
				mineField[row][col].mine = true;
				vecOfMinePtrs.push_back(&mineField[row][col]);
			}
			else {
				mineField[row][col].mine = false;
			}

		}
		row++;
	}

	PrintBoard();
	gameLoop();
}