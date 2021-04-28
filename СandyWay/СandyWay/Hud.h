#pragma once
#include <iostream>
#include "Header.h"

using namespace sf;
class Hud
{
private:

public:

	sf::Text gameOverText;
	sf::Font font;
	Image image;
	Texture t;
	Sprite s;
	int max;
	int key=0;
	RectangleShape bar;

	Hud();

	void initGUI();
	void Reset();
	void update(int k);
	void draw(RenderWindow& window);
};

