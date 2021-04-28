#include "Player.h"
#include <iostream>

#include "Game.h"
float centerWindow = 1366/2;
void Player::initVariables()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	this->hpMax = 100;
	this->hp = this->hpMax;
	setPosition(0,490);
	loseGame = 0;
	stopJump = 0;
	rect = sf::FloatRect(100, 180, 16, 16); //test
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Texture/player_sheet6.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 40, 50);

	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(3.f, 3.f);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->velocityMax = 10.f;
	this->velocityMin = 1.f;
	this->acceleration = 3.0f;
	this->drag = 0.85f;
	this->gravity = 4.f;
	this->velocityMaxY = 15.f;
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();
}

Player::~Player()
{

}

void Player::NewGame()
{
	this->initVariables();
	this->loseHp(1);
}

const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch;
}

const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::loseU()
{
	loseGame = 1;
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0) {
		this->hp = 0;
		std::cout << hp << std::endl;
	}
	else {

		std::cout << hp << std::endl;
	}
}




void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
	this->velocity.x += dir_x * this->acceleration;
	this->velocity.y += dir_y *5.0f;
	std::cout << velocity.x << std::endl;
	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
		view.move(velocity.x-((this->velocity.x < 0.f) ? -1.6 : 1.6), 0);
	}
	if (stopJump == 0 && velocity.y>4) {

		std::cout << velocity.y << " " << velocityMaxY << " " << stopJump << std::endl;

		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? 2.f : -2.f);
		if (abs(this->velocity.y) > 10.0f) {
			std::cout <<  "alooo "  << std::endl;
			stopJump = 1;
		}
	}

}

void Player::updatePhysics()
{
	this->velocity.y += 1.0 * this->gravity;
	if (std::abs(this->velocity.x) > this->velocityMaxY)
	{
		this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
	}

	this->velocity *= this->drag;

	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->velocityMin) 
		this->velocity.y = 0.f;
	if (stopJump==1) {
		if (std::abs(this->velocity.y) < 2.0f) {
			std::cout << "alooo 2" << std::endl;
			stopJump = 0;
		}
	}
	

	
	this->sprite.move(this->velocity);



}


void Player::updateMovement()
{
	if (hp > 0) {
		this->animState = PLAYER_ANIMATION_STATES::IDLE;
	}
	else {
		this->animState = PLAYER_ANIMATION_STATES::DEAD;
	}
		if (loseGame == 0) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			{
				this->move(-1.f, 0.f);
				this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				this->move(1.f, 0.f);
				this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
				
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			{
				this->move(0.f, 1.f);
				this->animState = PLAYER_ANIMATION_STATES::JUMPING;

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			{
				this->sprite.move(0.f, 1.f);
				this->loseHp(1);
			}
		}
	
}

void Player::updateAnimations()
{
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left > 160.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 50.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left > 360.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}

		this->sprite.setScale(3.f, 3.f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 50.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left > 360.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}

		this->sprite.setScale(-3.f, 3.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 3.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::JUMPING)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 50.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left > 360.f)
				this->currentFrame.left = 0;
			this->sprite.setScale(3.f, 3.f);
			this->sprite.setOrigin(0.f, 0.f);
		}
		this->sprite.setScale(3.f, 3.f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::DEAD)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->currentFrame.top = 125.f;
			this->currentFrame.left = 301.f;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else
		this->animationTimer.restart();
}

void Player::update()
{
	this->updateMovement();

	this->updateAnimations();
	this->updatePhysics();

}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}