#include "Graphics.h"

bool Graphics::gameLoop() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		repaint();
		return true;
	}
	return false;
}

void Graphics::repaint() {
	window.clear();
	
	/*Draw graphics here*/
	sf::CircleShape a(150);
	a.setFillColor(sf::Color::Green);
	window.draw(a);

	window.draw(spriteMap["face_happy"]);






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

Graphics::Graphics()
	: window(sf::VideoMode(WIDTH, HEIGHT), "Minesweeper") {
	loadSprites();
}