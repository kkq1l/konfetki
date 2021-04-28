#pragma once

#include "Header.h"
#include "Player.h" 
#include <string>
#include <sstream>

class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;


	sf::Font font;
	sf::Text pointText;

	Player* player;

	float spawnTimer;
	float spawnTimerMax;

	void initWindow();
	void initPlayer();

	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

public:


	sf::Image map_image;
	sf::Texture map;
	sf::Sprite s_map;

	Game();
	virtual ~Game();

	void initMap();

	void updateHealth();//test
	void updatePlayer();
	void updateCollision();
	void update();
	void renderPlayer();
	void render();
	const sf::RenderWindow& getWindow() const;

};
