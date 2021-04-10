#include "Game.h"
#include "Hud.h"
#include<map>
#include<string>
#include<sstream>
using namespace sf;

bool isMenu = 1;
float x, y = 0;
Hud lifeBarPlayer;//

float dx, dy;

void Game::initWindow()
{
	window.create(sf::VideoMode(1136, 640), "CandyWay", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);
}

void Game::initPlayer()
{
	player = new Player();
}

void Game::initVrags()
{
	spawnTimerMax = 50.f;
	spawnTimer = spawnTimerMax;
}

void Game::initWorld()
{
	worldBackgroundTex.loadFromFile("Texture/world/back.png");
	

	worldBackground.setTexture(worldBackgroundTex);
}

Game::Game()
{
	initWindow();
	initPlayer();
	initGUI();
	lifeBarPlayer.update(player->getHp());//test
	initVrags();
	initWorld();
}

Game::~Game()
{
	delete player;
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

void Game::updateWorld()
{

}

void Game::initGUI()
{

	
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
					isMenu = false; this->window.clear();
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

		updatePlayer();
		updateCollision();
		updateWorld();
	}
}





void Game::renderPlayer()
{
	player->render(window);
	window.setView(player->view);
}

void Game::render()
{
	const int H = 41;
	const int W = 150;
	Texture tileSet;
	float offsetX = 0, offsetY = 0;
	tileSet.loadFromFile("Texture/Mario_tileset.png");
	Sprite tile(tileSet);
	String TileMap[H] = {
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"                                                                                                                                                      ",
"P                                                                                                                                                     ",
"P                                                                                                                                                     ",
"P                 P                                           P                                   P                                                  P",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
	};

	bool onGround;
	std::cout << player->getPosition().x<<std::endl;

	FloatRect rect;
	int num = 0;
	rect = FloatRect(100, 180, 16, 16);
	for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
		for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
		{
			if ((TileMap[i][j] == 'P') || (TileMap[i][j] == 'k') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'r') || (TileMap[i][j] == 't'))
			{
				if (dy > 0 && num == 1)
				{
					rect.top = i * 16 - rect.height;  dy = 0;   onGround = true;
				}
				if (dy < 0 && num == 1)
				{
					rect.top = i * 16 + 16;   dy = 0;
				}
				if (dx > 0 && num == 0)
				{
					rect.left = j * 16 - rect.width;
				}
				if (dx < 0 && num == 0)
				{
					rect.left = j * 16 + 16;
				}
			}

			if (TileMap[i][j] == 'c') {
				// TileMap[i][j]=' '; 
			}
		}

	window.clear();
//<<<<<<< HEAD
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
		{
			if (TileMap[i][j] == 'P')  tile.setTextureRect(IntRect(143 - 16 * 3, 112, 16, 16));

			if (TileMap[i][j] == 'k')  tile.setTextureRect(IntRect(143, 112, 16, 16));

			if (TileMap[i][j] == 'c')  tile.setTextureRect(IntRect(143 - 16, 112, 16, 16));

			if (TileMap[i][j] == 't')  tile.setTextureRect(IntRect(0, 47, 32, 95 - 47));

			if (TileMap[i][j] == 'g')  tile.setTextureRect(IntRect(0, 16 * 9 - 5, 3 * 16, 16 * 2 + 5));

			if (TileMap[i][j] == 'G')  tile.setTextureRect(IntRect(145, 222, 222 - 145, 255 - 222));

			if (TileMap[i][j] == 'd')  tile.setTextureRect(IntRect(0, 106, 74, 127 - 106));

			if (TileMap[i][j] == 'w')  tile.setTextureRect(IntRect(99, 224, 140 - 99, 255 - 224));

			if (TileMap[i][j] == 'r')  tile.setTextureRect(IntRect(143 - 32, 112, 16, 16));

			if ((TileMap[i][j] == ' ') || (TileMap[i][j] == '0')) continue;

			tile.setPosition(j * 16 - offsetX, i * 16 - offsetY);
			window.draw(tile);
		}

	
//=======
	renderWorld();

//>>>>>>> c8048320f964f0b986e1e31740d8bd3617ad0363
	if (player->getHp() <= 0) {
		
		player->loseU();
		window.draw(gameOverText);
	}
	renderPlayer();
	updateHealth(); //test
	window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	return window;
}

void Game::renderWorld()
{
	//window.draw(worldBackground);
}