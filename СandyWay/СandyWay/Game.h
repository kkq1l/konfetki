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
	Hud* huddd;
	float spawnTimer;
	float spawnTimerMax;
	void initWindow();
	void initPlayer();

	int viewX, viewY;
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

public:


	sf::Image map_image;
	sf::Texture map;
	sf::Sprite s_map;

	bool gaming;
	Game();
	virtual ~Game();
	void mapGener();
	void updateHealth();//test
	void updatePlayer();
	void updateCollision();
	void update();
	void renderPlayer();
	void render();
	const sf::RenderWindow& getWindow() const;

};
