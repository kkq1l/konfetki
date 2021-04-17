#include "Hud.h"
int key=0;
Hud::Hud()
{
	image.loadFromFile("Texture/life.png");
	image.createMaskFromColor(Color(50, 96, 166));
	t.loadFromImage(image);
	s.setTexture(t);
	s.setTextureRect(IntRect(783, 2, 15, 84));

	bar.setFillColor(Color(0, 0, 0));
	max = 100;
}

void Hud::initGUI()
{
	font.loadFromFile("Fonts/PixellettersFull.ttf");

	gameOverText.setFont(font);
	gameOverText.setCharacterSize(60);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setString("Game Over!");
	gameOverText.setPosition(555, 300);
}

void Hud::update(int k)
{
	if (k > 1) {

		if (k < max)
			bar.setSize(Vector2f(10, (max - k) * 70 / max));
	}
	else {
		key = 1;
	}
}

void Hud::draw(RenderWindow& window)
{
	
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();
	if (key == 1) {
		font.loadFromFile("Fonts/PixellettersFull.ttf");

		gameOverText.setFont(font);
		gameOverText.setCharacterSize(60);
		gameOverText.setFillColor(sf::Color::Red);
		gameOverText.setString("Game Over!");
		gameOverText.setPosition(center.x-100, center.y);
		window.draw(gameOverText);
	}
	s.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 10);
	bar.setPosition(center.x - size.x / 2 + 14, center.y - size.y / 2 + 14);

	window.draw(s);
	window.draw(bar);
}

