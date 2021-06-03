#include "Game.h"
#include "Hud.h"
#include<map>
#include<string>
#include<sstream>
using namespace sf;

bool isMenu = 1;
float x, y = 0;
Hud lifeBarPlayer;//
const int H = 30;
const int W = 150;
Texture tileSet;
float offsetX = 0, offsetY = 0;
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
	"                                                                                                  S                                                   ",
	"                                                              S                                   S                                                  P",
	"                  PPPPPPPPPPPPPPPPPPPGGGGGGGGGGPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP" };



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
	initWindow();
	initPlayer();
	gaming = false;
	lifeBarPlayer.update(player->getHp());
}

Game::~Game()
{
	delete player;
}

void Game::mapGener()
{
	tileSet.loadFromFile("Texture/tileset.png");
	std::cout << "asd" << std::endl;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++)
		{
			if (TileMap[i][j] == 'P')  tile.setTextureRect(IntRect(143 - 16 * 3, 112, 32, 32));
			if (TileMap[i][j] == 'S')  tile.setTextureRect(IntRect(143 - 16 * 3, 112, 32, 32));
			if (TileMap[i][j] == 'G')  tile.setTextureRect(IntRect(143 - 16 * 3, 112, 16, 16));
			if ((TileMap[i][j] == ' ') || (TileMap[i][j] == '0')) continue;

			tile.setPosition(j * 16 - offsetX, i * 16 - offsetY);
			window.draw(tile);
		}
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
	


	for (int i = (player->getPosition().y / 16); i < ((player->getPosition().y + player->getGlobalBounds().height) / 16); i++)
		for (int j = (player->getPosition().x / 16); j < ((player->getPosition().x + player->getGlobalBounds().width) / 16); j++)
		{
			std::cout << "Pos po X: "<<player->getPosition().x / 16 << " Pos po Y: " << player->getPosition().y / 16 << " X:" << i << " Y:" << j << " "<< player->getGlobalBounds().height << TileMap[i][j] << std::endl;
			if (TileMap[i][j] == 80)
			{
				

				//if (player->getPosition().y + player->getGlobalBounds().height > window.getSize().y){
				player->resetVelocityY();
				player->setPosition(
					player->getPosition().x,
					i*16 - (player->getGlobalBounds().height)
						);
					//}
			}

			if (TileMap[i][j] == 'S' && player->velocity.x>0.f)
			{
				
				player->setPosition(
					j*16-player->getGlobalBounds().width,
					i * 16
				);
			}
			if (TileMap[i][j] == 'S' && player->velocity.x < 0.f)
			{
				player->setPosition(
					j * 16,
					i * 16
				);
			}
			if (TileMap[i][j] == 'G')
			{
				TileMap[i][j] = '0';
			}
			if (player->getPosition().y + player->getGlobalBounds().height > (window.getSize().y)+70)
			{
				player->setPosition(
					player->getPosition().x,
					(window.getSize().y - player->getGlobalBounds().height)+70
				);

				player->loseHp(100);
			}
		}
}

void Game::update()
{
	Texture menuTexture0, menuTexture1, menuTexture2, menuTexture3, aboutTexture;
	menuTexture0.loadFromFile("Texture/menu/menu.png");
	menuTexture1.loadFromFile("Texture/menu/btnplay.png");
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

					player->NewGame();
					isMenu = false;
					this->window.clear();
					player->view.reset(sf::FloatRect(0, 0, 1136, 640));
				}
				//if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
				if (menuNum == 2) {

					player->view.reset(sf::FloatRect(viewX + 0.6, 0, 1136, 640));
					isMenu = false;
					this->window.clear();
				}
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
				viewX = player->getPosition().x;
				viewY = player->getPosition().y;
				window.clear();
				gaming = true;
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
	}
}





void Game::renderPlayer()
{
	player->render(window);
	window.setView(player->view);
}

void Game::render()
{
	
	window.clear();

	mapGener();
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

