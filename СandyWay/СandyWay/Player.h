#pragma once
#include "Header.h"

enum PLAYER_ANIMATION_STATES { IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING,DEAD };

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;

	int hp;
	int hpMax;
	int loseGame=0;
	//Animation
	sf::IntRect currentFrame;
	bool animationSwitch;

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


	sf::FloatRect rect;
	bool onGround;
	float dx, dy;


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

	Player(String F, float X, float Y, float W, float H)///////////////////
	{
		state = stay; speed = 0; playerScore = 0; dx = 0; dy = 0;
		life = true; isMove = false; isSelect = false; onGroud = false;
	}

	enum { left, right, up, down, jump, stay } state; // perechislenie i sostoyanie
};