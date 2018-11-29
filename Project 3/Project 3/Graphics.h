#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>
//#include "Tile.h" //neccessary?
using namespace std;

class Game;

class Graphics {
	/*Connects the game to the graphics window (for tile loading)*/
	Game* game;

	/*Dimensions for the window height*/
	int WIDTH = 800, HEIGHT = 600;
	sf::RenderWindow window;

	/*Maps containing textures, Sprites*/
	map<string, sf::Texture> textureMap; //Should this use Texture references?
	map<string, sf::Sprite> spriteMap;
	
	/*Paints sprites.*/
	void repaint();
	void loadSprites();

public:
	Graphics(Game* g);
	
	/*Repaints window and checks if the window is X'ed out.*/
	void update();
	sf::Vector2i getMouseCoords() const;
};