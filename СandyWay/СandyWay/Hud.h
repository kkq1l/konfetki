#pragma once
#include <iostream>

#include <SFML\System.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\Network.hpp>

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

