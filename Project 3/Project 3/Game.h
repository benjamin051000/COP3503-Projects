#pragma once
#include <iostream>
using namespace std;

class Game {
	struct Mine {
		bool isMine;
		Mine(bool m = false);
	};
	
	static const int rows = 16, cols = 25;
	Mine mineField[rows][cols];
public:
	void PrintBoard() const;
	Game();
};