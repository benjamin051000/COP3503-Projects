#include "Graphics.h"

void Graphics::runWindow() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		repaint();
	}
}

void Graphics::repaint() {
	window.clear();
	/*Draw graphics here*/
	window.display();
}

Graphics::Graphics()
	: window(sf::VideoMode(WIDTH, HEIGHT), "Minesweeper") {
	/*Load textures into map*/
	
	
	runWindow();
}