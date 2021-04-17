#include "Game.h"
#include "Hud.h"
#include "Map.h"
#include<map>
#include<string>
#include<sstream>
using namespace sf;

bool isMenu = 1;
float x, y = 0;
Hud lifeBarPlayer;//

void Game::initWindow()
{
	window.create(sf::VideoMode(1136, 640), "CandyWay", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);
}

void Game::initPlayer()
{
	player = new Player();
}

Game::Game()
{
	initMap();
	initWindow();
	initPlayer();
	lifeBarPlayer.update(player->getHp());
}

Game::~Game()
{
	delete player;
}

void Game::initMap()
{
}

void Game::drawMap()
{

	map_image.loadFromFile("images/map.png");
	map.loadFromImage(map_image);
	s_map.setTexture(map);
	for (int i = 0; i < 25; i++)
		for (int j = 0; j < 40; j++)
		{
			if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик


			s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

			window.draw(s_map);//рисуем квадратики на экран
		}
}

void Game::updateHealth()
{
	lifeBarPlayer.update(player->getHp());
	lifeBarPlayer.draw(window);
}

void Game::updatePlayer()
{
	player->update();
}

void Game::updateCollision()
{
	if (player->getPosition().y + player->getGlobalBounds().height > window.getSize().y)
	{
		player->resetVelocityY();
		player->setPosition(
			player->getPosition().x,
			window.getSize().y - player->getGlobalBounds().height
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

	Sprite menu0(menuTexture0), menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), ingame(aboutTexture);
	int menuNum = 0;
	menu1.setPosition(635, 200);
	menu2.setPosition(850, 200);
	menu3.setPosition(635, 320);

	while (isMenu)
	{
		while (window.pollEvent(ev)) {
			menu0.setColor(Color::White);
			menu1.setColor(Color::White);
			menu2.setColor(Color::White);
			menu3.setColor(Color::White);
			ingame.setColor(Color::White);
			menuNum = 0;
			window.draw(menu0);

			if (IntRect(635, 200, 200, 100).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
			if (IntRect(850, 200, 200, 100).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
			if (IntRect(635, 320, 200, 100).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (menuNum == 1) {
					isMenu = false; 
					this->window.clear();
					player->view.reset(sf::FloatRect(0, 0, 1136, 640));
				}
				if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
				if (menuNum == 3) { window.close(); isMenu = false; }

			}

			window.draw(menu1);
			window.draw(menu2);
			window.draw(menu3);

			window.display();
		}
	}
	if (isMenu==false) {
		window.draw(menu0);

		while (window.pollEvent(ev))
		{

			if (ev.type == sf::Event::Closed)
				window.close();
			else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
			{
				player->view.reset(sf::FloatRect(0, 0, 1136, 640));
				window.clear();
				isMenu = true;
			}


			if (ev.type == sf::Event::KeyReleased && (
					ev.key.code == sf::Keyboard::A ||
					ev.key.code == sf::Keyboard::D ||
					ev.key.code == sf::Keyboard::W ||
					ev.key.code == sf::Keyboard::S
					)
				)
			{
				player->resetAnimationTimer();
			}
		}





		drawMap();
		updatePlayer();
		updateCollision();
	}
}





void Game::renderPlayer()
{
	player->render(window);
	window.setView(player->view);
}

void Game::render()
{
	if (player->getHp() <= 0) {
		
		player->loseU();
	}
	renderPlayer();
	updateHealth(); //test
	window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	return window;
}

