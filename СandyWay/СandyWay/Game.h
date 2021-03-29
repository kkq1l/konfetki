#pragma once

#include "Header.h"
#include "Player.h" 

class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;

	Player* player;

	void initWindow();
	void initPlayer();

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
