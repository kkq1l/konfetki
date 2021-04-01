#include "Vrag.h"
#include <iostream>

#include "Game.h"

void Vrag::initVariables()
{
	/*this->pointCount = rand() % 8 + 3; //min = 3 max = 10
	this->type = 0;
	this->speed = static_cast<float>(this->pointCount / 3);
	this->hpMax = static_cast<int>(this->pointCount);
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->points = this->pointCount;*/
	
	this->hpMax = 100;
	this->hp = this->hpMax;
}

void Vrag::initTexture()
{
	if (!this->textureSheet.loadFromFile("Texture/player_sheet.png"))
	{
		std::cout << "ERROR::PLAYER::Could not load the player sheet!" << "\n";
	}
}

void Vrag::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 40, 50); 

	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(3.f, 3.f);
}

void Vrag::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

Vrag::Vrag()
{
	this->initVariables();
	this->initShape();
	this->initTexture();
	this->initAnimations();
}

Vrag::~Vrag()
{

}












void Vrag::initShape()
{
	this->shape.setRadius(this->pointCount * 5);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}


//Accessors
const sf::FloatRect Vrag::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Vrag::getPoints() const
{
	return this->points;
}

const int& Vrag::getDamage() const
{
	return this->damage;
}

//Functions
void Vrag::update()
{
	this->shape.move(0.f, this->speed);
}

void Vrag::rendervrag(sf::RenderTarget* target)
{
	target->draw(this->shape);
}