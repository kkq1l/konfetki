#pragma once
#include "Header.h"
#include "Hud.h"
enum PLAYER_ANIMATION_STATES { IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING,DEAD };

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;
	Hud* hudd;
	int hp;
	int hpMax;
	int loseGame=0;
	//Animation
	sf::IntRect currentFrame;
	bool animationSwitch;
	bool stopJump;
	//Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxY;
	

	//Core

	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
	void initPhysics();

public:
	Player();
	virtual ~Player();
	sf::View view;

	//test vzaimodeystvie s kartoy

	void NewGame();
	sf::FloatRect rect;
	bool onGround;
	float dx, dy;
	bool yaStolknulsya;

	const bool& getAnimSwitch();
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	short animState;

	const int& getHp() const;
	const int& getHpMax() const;

	void setPosition(const float x, const float y);
	void resetVelocityY();

	void loseU();
	void setHp(const int hp);
	void loseHp(const int value);


	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void updatePhysics();
	void updateMovement();
	void updateAnimations();
	void update();
	void render(sf::RenderTarget& target);
};