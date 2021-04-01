
#ifndef VRAG_H
#define VRAG_H

#include "Header.h"

class Vrag
{
private:
	unsigned pointCount;
	sf::CircleShape shape;
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;

	short animState;
	sf::IntRect currentFrame;
	bool animationSwitch;

	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initVariables();
	void initShape();
	void initTexture();
	void initSprite();
	void initAnimations();

public:
	Vrag();
	virtual ~Vrag();

	//Accessors
	const bool& getAnimSwitch();
	const sf::FloatRect getBounds() const;
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;
	const int& getHp() const;
	const int& getHpMax() const;

	void setPosition(const float x, const float y);
	void resetVelocityY();

	//Functionsvoid setHp(const int hp);
	void loseHp(const int value);


	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void update();
	void rendervrag(sf::RenderTarget& target);
};

#endif //!VRAG_H
