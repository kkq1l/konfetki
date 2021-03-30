#include "Game.h"
#include "Hud.h"
#include<map>
#include<string>
#include<sstream>
using namespace sf;

bool isMenu = 1;
float x, y = 0;
Hud lifeBarPlayer;//test
void Game::initWindow()
{
	this->window.create(sf::VideoMode(1136, 640), "CandyWay", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);

}

void Game::initPlayer()
{
	this->player = new Player();
}

Game::Game()
{
	this->initWindow();
	this->initPlayer();
	this->initGUI();
	lifeBarPlayer.update(player->getHp());//test
}

Game::~Game()
{
	delete this->player;
}




//test
void Game::updateHealth()
{
	lifeBarPlayer.update(player->getHp());
	lifeBarPlayer.draw(window);
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
void Game::initGUI()
{
	font.loadFromFile("Fonts/PixellettersFull.ttf");
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window.getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 22.f,
		this->window.getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 22.f);
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
			}//если нажали первую кнопку, то выходим из меню 
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
				player->view.reset(sf::FloatRect(0, 0, 1136, 640));
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

	window.setView(player->view);
	this->player->render(this->window);
}

void Game::render()
{
	this->window.clear();
	if (this->player->getHp() <= 0)
		this->window.draw(this->gameOverText);
	this->renderPlayer();
	this->updateHealth(); //test
	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}