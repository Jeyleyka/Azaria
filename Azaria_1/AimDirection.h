#pragma once

#include "Entity.h"

#define PI 3.1415926535f

class AimDirection
{
private:
	// Variables
	sf::RectangleShape rectangle;
	sf::Vector2f direction;
	sf::Vector2f rectangePos;
	sf::CircleShape circle;

	float distance;
	float offsetX;
	float offsetY;
	float angle;

public:
	// Constructor/Destructor
	AimDirection();
	~AimDirection();

	// Functions
	const sf::Vector2f& getPosition() const;
	const sf::Vector2f& getSize() const;
	const float& getAngle() const;
	const sf::RectangleShape& getShape() const;
	void update(sf::Vector2f mousepos, Entity* player);
	void render(sf::RenderTarget& target);
};

