#pragma once

#include "Header.h"
#include "Player.h" 
#include "Vrag.h"
#include <string>
#include <sstream>

class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;


	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;

	Player* player;

	float spawnTimer;
	float spawnTimerMax;
	std::vector<Vrag*>vrags;

	void initWindow();
	void initPlayer();
	void initVrags();
	void initWorld();
	void initGUI();
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

public:



	Game();
	virtual ~Game();


	void updateHealth();//test
	void updatePlayer();
	void updateCollision();
	void updateVrags();
	void update();
	void renderPlayer();
	void render();
	void updateWorld();
	void renderWorld();
	const sf::RenderWindow& getWindow() const;

};
