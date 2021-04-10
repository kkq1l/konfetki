#include "Player.h"
#include <iostream>

#include "Game.h"

void Player::initVariables()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	this->hpMax = 100;
	this->hp = this->hpMax;
	

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
<<<<<<< HEAD
	this->currentFrame = sf::IntRect(0, 0, 40, 50); 
=======
	this->currentFrame = sf::IntRect(0, 0, 40, 50);
>>>>>>> 7e56b8ec1645500ce0c40a09c06e60ebe48b1faa

	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(3.f, 3.f);
	sprite.setPosition(x + w / 2, y + h / 2);////////
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

<<<<<<< HEAD
=======



>>>>>>> 7e56b8ec1645500ce0c40a09c06e60ebe48b1faa
void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y) ///nujno zakomentir
{
	this->velocity.x += dir_x * this->acceleration;

	if (std::abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
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

	this->sprite.move(this->velocity);

<<<<<<< HEAD
void Player::updateMovement()
{


	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	if (loseGame==0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			this->move(-1.f, 0.f);
			this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			this->move(1.f, 0.f);
			this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
=======
>>>>>>> 7e56b8ec1645500ce0c40a09c06e60ebe48b1faa


}

<<<<<<< HEAD
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			this->move(0.f, -1.f);
			this->animState = PLAYER_ANIMATION_STATES::JUMPING;
			currentFrame += 0.005 * time;
			if (currentFrame > 3) currentFrame -= 3;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			this->sprite.move(0.f, 1.f);
			this->loseHp(1);
		}
	} */
=======

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
				view.setCenter(getPosition().x, getPosition().y);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				this->move(1.f, 0.f);
				this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
				view.setCenter(getPosition().x, getPosition().y);


			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			{
				this->move(0.f, -1.f);
				//this->animState = PLAYER_ANIMATION_STATES::JUMPING;

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			{
				this->sprite.move(0.f, 1.f);
				this->loseHp(1);
			}
		}
	
>>>>>>> 7e56b8ec1645500ce0c40a09c06e60ebe48b1faa
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