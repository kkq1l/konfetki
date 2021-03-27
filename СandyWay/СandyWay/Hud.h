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

	Hud()
	{
		image.loadFromFile("Texture/life.png");
		if (!image.loadFromFile("Texture/life.png"))
		{
			std::cout << "ERROR::HUD::Could not load the player sheet!" << "\n";
		}
		else {
			std::cout << "DONE::HUD" << "\n";
		}
		image.createMaskFromColor(Color(50, 96, 166));
		t.loadFromImage(image);
		s.setTexture(t);
		s.setTextureRect(IntRect(783, 2, 15, 84));

		bar.setFillColor(Color(0, 0, 0));
		max = 100;
	}

	void update(int k)

	{
		if (k > 0)
			if (k < max)
				bar.setSize(Vector2f(10, (max - k) * 70 / max));
	}

	void draw(RenderWindow& window)
	{
		Vector2f center = window.getView().getCenter();
		Vector2f size = window.getView().getSize();

		s.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 10);
		bar.setPosition(center.x - size.x / 2 + 14, center.y - size.y / 2 + 14);

		window.draw(s);
		window.draw(bar);
	}
};

