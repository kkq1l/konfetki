#pragma once
#include <iostream>
#include "Header.h"

using namespace sf;
class Hud
{
public:

	sf::Text gameOverText;
	sf::Font font;
	Image image;
	Texture t;
	Sprite s;
	int max;
	RectangleShape bar;

	Hud();

	void initGUI();

	void update(int k);
	void draw(RenderWindow& window);
};

