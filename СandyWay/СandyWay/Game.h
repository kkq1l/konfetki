#pragma once

#include "Header.h"
#include "Player.h" 

class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;


	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;

	Player* player;

	void initWindow();
	void initPlayer();

	void initGUI();
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;


public:



	Game();
	virtual ~Game();


	void updateHealth();//test
	void updatePlayer();
	void updateCollision();
	void update();
	void renderPlayer();
	void render();
	const sf::RenderWindow& getWindow() const;
};
