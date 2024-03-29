#include "Graphics.h"
#include "Game.h"

void Graphics::update() {
	if (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				game->StopRunning();
				window.close();
				return;
			}
		}
		repaint();
	}
}

sf::Vector2i Graphics::getMouseCoords() const {
	return sf::Mouse::getPosition(window);
}

void Graphics::repaint() {
	window.clear();
	
	/*Draw minefield*/
	for (int r = 0; r < game->GetRows(); r++) {
		for (int c = 0; c < game->GetCols(); c++) {
			
			/*offset by 32 pixels each iteration*/
			Tile tile = game->getTile(r, c);
			sf::Sprite tileSprite;

			if (tile.revealed) {
				tileSprite = spriteMap["tile_revealed"];
			}
			else {
				tileSprite = spriteMap["tile_hidden"];
			}

			tileSprite.setPosition(sf::Vector2f(32.f * c, 32.f * r));
			window.draw(tileSprite);

			/*Overlay mines, flags, and numbers*/
			if (tile.flagged) {
				tileSprite = spriteMap["flag"];
			}
			else if ((tile.revealed || game->debug) && tile.mine) {
				tileSprite = spriteMap["mine"];
			}
			else {
				/*Display number of adjacent mines*/
				tileSprite = spriteMap["number_" + to_string(tile.nearbyMines)];
			}

			tileSprite.setPosition(sf::Vector2f(32.f * c, 32.f * r));
			window.draw(tileSprite);
		}
	}

	/*Draw MinesLeft numbers*/
	sf::Sprite minesLeftTens, minesLeftOnes;
	unsigned short minesLeft = game->GetMinesLeft();
	short tensDigitBegin, onesDigitBegin;

	tensDigitBegin = minesLeft / 10 * 21;
	onesDigitBegin = minesLeft % 10 * 21;

	minesLeftTens = spriteMap["digits"];
	minesLeftTens.setTextureRect(sf::IntRect(tensDigitBegin, 0, 21, 32));
	minesLeftTens.setPosition(numberCoordsTens);
	window.draw(minesLeftTens);

	minesLeftOnes = spriteMap["digits"];
	minesLeftOnes.setTextureRect(sf::IntRect(onesDigitBegin, 0, 21, 32));
	minesLeftOnes.setPosition(numberCoordsOnes);
	window.draw(minesLeftOnes);


	/*Draw bottom sprites*/
	sf::Sprite face = game->WinCondition() ? spriteMap["face_win"] : //goes to next line
						game->gameover ? spriteMap["face_lose"] : spriteMap["face_happy"];

	face.setPosition(faceCoords);
	window.draw(face);

	pair<sf::Sprite*, sf::Vector2f*> menuOpts[3];
	menuOpts[0] = pair<sf::Sprite*, sf::Vector2f*>(&spriteMap["debug"], &debugCoords);
	menuOpts[1] = pair<sf::Sprite*, sf::Vector2f*>(&spriteMap["test_1"], &test1Coords);
	menuOpts[2] = pair<sf::Sprite*, sf::Vector2f*>(&spriteMap["test_2"], &test2Coords);

	for (pair<sf::Sprite*, sf::Vector2f*> buttonTemp : menuOpts) {
		sf::Sprite button = *buttonTemp.first;
		button.setPosition(*buttonTemp.second);
		window.draw(button);
	}

	/*Finally, display the window*/
	window.display();
}

void Graphics::loadSprites() {
	/*Load textures into map*/
	string imageFileNames[] = { "mine.png", "tile_hidden.png", "tile_revealed.png",
						"flag.png",	"face_happy.png", "face_win.png", "face_lose.png",
						"digits.png", "debug.png", "test_1.png", "test_2.png" };
	
	sf::Texture texture;
	for (string imageName : imageFileNames) {
		string imageTitle = imageName.substr(0, imageName.find("."));
		
		if (!texture.loadFromFile("images\\" + imageName)) {
			//sfml automatically outputs errors
		}

		texture.setSmooth(true); 
		textureMap.emplace(imageTitle, texture);
	}

	/*Add number textures*/
	for (int i = 1; i <= 8; i++) {
		string imageFileName = "number_#.png";

		char num = '0' + i;
		replace(imageFileName.begin(), imageFileName.end(), '#', num);

		string imageTitle = imageFileName.substr(0, imageFileName.find("."));

		/*sf::Texture texture;*/
		if (!texture.loadFromFile("images\\" + imageFileName)) {
			//sfml automatically outputs errors
		}

		texture.setSmooth(true);
		textureMap.emplace(imageTitle, texture);
	}

	/*Create sprites and load them into spriteMap*/
	sf::Sprite sprite;
	for (map<string, sf::Texture>::iterator iter = textureMap.begin(); iter != textureMap.end(); iter++) {
		sprite = sf::Sprite(iter->second);
		spriteMap.emplace(iter->first, sprite);
	}
}

Graphics::Graphics(Game* g)
	: window(sf::VideoMode(WIDTH, HEIGHT), "Minesweeper", sf::Style::Titlebar | sf::Style::Close) {
	game = g;

	loadSprites();

	/*Load menu coords*/
	float x_base = WIDTH / 2 - 32.f,
		y_base = 16 * 32.f;
	faceCoords = sf::Vector2f(x_base, y_base);
	debugCoords = sf::Vector2f(x_base + 64 * 2, y_base);
	test1Coords = sf::Vector2f(x_base + 64 * 3, y_base);
	test2Coords = sf::Vector2f(x_base + 64 * 4, y_base);
	numberCoordsTens = sf::Vector2f(0, y_base);
	numberCoordsOnes = sf::Vector2f(21, y_base);
}

Graphics::~Graphics() {
}