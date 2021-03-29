#pragma once
#include <iostream>
#include "Header.h"

using namespace sf;
class Hud
{
public:
	Image image;
	Texture t;
	Sprite s;
	int max;
	RectangleShape bar;

	Hud();

	void update(int k);

	void draw(RenderWindow& window);
};

