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
			Tile tile = game->getTile(r, c); //Get a pointer? for speed or nah
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
				tileSprite.setPosition(sf::Vector2f(32.f * c, 32.f * r));
				window.draw(tileSprite);
			}
			else if ((tile.revealed || tile.debug) && tile.mine) {
				tileSprite = spriteMap["mine"];
				tileSprite.setPosition(sf::Vector2f(32.f * c, 32.f * r));
				window.draw(tileSprite);
			}
			else {
				/*Display number of adjacent mines*/
			}

		}
	}

	/*Draw bottom sprites*/	//This could be looped with an array of strings and ints or something, lessens number of sprites in mem (?)
	sf::Sprite face;
	if (game->gameover) {
		face = spriteMap["face_lose"];
	}
	else {
		face = spriteMap["face_happy"];
	}
	
	face.setPosition(faceCoords); //Is this an acceptable position for the face?
	window.draw(face);

	sf::Sprite debugButton = spriteMap["debug"];
	debugButton.setPosition(debugCoords);
	window.draw(debugButton);

	sf::Vector2f testCoords[] = {test1Coords, test2Coords};

	for (int i = 1; i <= 2; i++) {
		sf::Sprite testi = spriteMap["test_" + to_string(i)];
		testi.setPosition(testCoords[i - 1]);
		window.draw(testi);
	}

	/*Finally, display the window*/
	window.display();
}

void Graphics::loadSprites() {
	/*Load textures into map*/
	string imageFileNames[] = { "mine.png", "tile_hidden.png", "tile_revealed.png",
						"flag.png",	"face_happy.png", "face_win.png", "face_lose.png",
						"digits.png", "debug.png", "test_1.png", "test_2.png" };

	for (string imageName : imageFileNames) {
		string imageTitle = imageName.substr(0, imageName.find("."));

		sf::Texture texture;
		if (!texture.loadFromFile("images\\" + imageName)) {
			//sfml automatically outputs errors
		}

		texture.setSmooth(true); //Should we be smoothing here?
		textureMap.emplace(imageTitle, texture);
	}

	/*Add number textures*/
	for (int i = 1; i <= 8; i++) {
		string imageFileName = "number_#.png";

		char num = '0' + i;
		replace(imageFileName.begin(), imageFileName.end(), '#', num);

		string imageTitle = imageFileName.substr(0, imageFileName.find("."));

		sf::Texture texture;
		if (!texture.loadFromFile("images\\" + imageFileName)) {
			//sfml automatically outputs errors
		}

		texture.setSmooth(true); //Should we be smoothing here?
		textureMap.emplace(imageTitle, texture);
	}


	/*Create sprites and load them into spriteMap*/
	for (map<string, sf::Texture>::iterator iter = textureMap.begin(); iter != textureMap.end(); iter++) {
		sf::Sprite sprite(iter->second);
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
}