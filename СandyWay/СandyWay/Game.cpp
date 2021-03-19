#include "Game.h"
using namespace sf;

bool isMenu = 1;
float x, y = 0;
void Game::initWindow()
{
	this->window.create(sf::VideoMode(1136, 668), "CandyWay", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 1136, 668));//

}

void Game::initPlayer()
{
	this->player = new Player();
}

Game::Game()
{
	this->initWindow();
	this->initPlayer();
}

Game::~Game()
{
	delete this->player;
}



void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateCollision()
{
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y)
	{
		this->player->resetVelocityY();
		this->player->setPosition(
			this->player->getPosition().x,
			this->window.getSize().y - this->player->getGlobalBounds().height
		);
	}
}

void Game::update()
{
	Texture menuTexture0, menuTexture1, menuTexture2, menuTexture3, aboutTexture;
	menuTexture0.loadFromFile("Texture/menu/menu.png");
	menuTexture1.loadFromFile("Texture/menu/btnplay.png");
	menuTexture2.loadFromFile("Texture/menu/btnplay.png");
	menuTexture3.loadFromFile("Texture/menu/btnquit.png");
	aboutTexture.loadFromFile("Texture/menu/menu.png");
	Sprite menu0(menuTexture0), menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture);
	int menuNum = 0;
	menu1.setPosition(635, 200);
	menu2.setPosition(850, 200);
	menu3.setPosition(635, 320);

	while (isMenu)
	{
		menu0.setColor(Color::White);
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.draw(menu0);

		if (IntRect(635, 200, 200, 100).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(850, 200, 200, 100).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(635, 320, 200, 100).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) {
				isMenu = false; this -> window.clear();
			}//���� ������ ������ ������, �� ������� �� ���� 
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
	if (isMenu==false) {
		while (this->window.pollEvent(this->ev))
		{
			if (this->ev.type == sf::Event::Closed)
				this->window.close();
			else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
			{
				this->window.clear();
				isMenu = true;
			}


			if (
				this->ev.type == sf::Event::KeyReleased &&
				(
					this->ev.key.code == sf::Keyboard::A ||
					this->ev.key.code == sf::Keyboard::D ||
					this->ev.key.code == sf::Keyboard::W ||
					this->ev.key.code == sf::Keyboard::S
					)
				)
			{
				this->player->resetAnimationTimer();
			}
		}

		this->updatePlayer();

		this->updateCollision();
	}
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::render()
{
	this->window.clear();

	this->renderPlayer();

	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}