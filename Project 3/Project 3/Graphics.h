#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Game;

class Graphics {
	/*Connects the game to the graphics window.*/
	Game* game;

	/*Dimensions for the window height*/
	static const short WIDTH = 800, HEIGHT = 600;
	sf::RenderWindow window;

	/*Maps containing textures, Sprites*/
	map<string, sf::Texture> textureMap;
	map<string, sf::Sprite> spriteMap;
	
	/*Paints sprites.*/
	void repaint();

	/*Loads sprites into spriteMap from Textures.*/
	void loadSprites();

public:
	Graphics(Game* g);
	~Graphics();

	/*Repaints window and checks if the window is X'ed out.*/
	void update();

	/*Returns mouse coordinates. For gameLoop.*/
	sf::Vector2i getMouseCoords() const;
	
	/*Menu button coords. Used for mouse positioning.*/
	sf::Vector2f faceCoords,
				 debugCoords,
				 test1Coords,
				 test2Coords;
};