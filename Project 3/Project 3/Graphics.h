#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <map>
using namespace std;

class Graphics {
	/*Dimensions for the window height*/
	int WIDTH = 800, HEIGHT = 600;
	sf::RenderWindow window;

	/*Map containing textures*/
	map<string, string> textureMap;

	void runWindow();
	void repaint();
	/*TODO: Sprites, textures, etc.*/
public:
	Graphics();
	
};