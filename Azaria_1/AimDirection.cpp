#include "stdafx.h"
#include "AimDirection.h"

// Constructor/Destructor
AimDirection::AimDirection()
{
	this->rectangle.setSize(sf::Vector2f(150.f, 25.f));
	this->rectangle.setFillColor(sf::Color(255, 255, 255, 150));
	this->rectangle.setOrigin(150.f, 12.5f);
	this->distance = 150.f;
	this->offsetX = 25.f;
	this->offsetY = 20.f;
	this->circle.setFillColor(sf::Color::Red);
	this->circle.setRadius(10.f);
}

AimDirection::~AimDirection()
{
}

const sf::Vector2f& AimDirection::getPosition() const
{
	return this->rectangle.getPosition();
}

const sf::Vector2f& AimDirection::getSize() const
{
	return this->rectangle.getSize();
}

const float& AimDirection::getAngle() const
{
	return this->angle;
}

const sf::RectangleShape& AimDirection::getShape() const
{
	return this->rectangle;
}

// Functions
void AimDirection::update(sf::Vector2f mousepos, Entity* player)
{
	this->direction = sf::Vector2f(mousepos) - player->GetPosition();
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	// Нормализуем направление (для того чтобы движение было равномерным)
	if (length > 1.0f) {
		direction /= length;  // Нормализуем
	}

	this->angle = std::atan2(this->direction.y, this->direction.x);

	/*this->rectangle.setPosition(player->GetPosition() + direction * distance);*/
	// Двигаем прямоугольник в сторону мыши
	this->rectangePos = player->GetPosition() + sf::Vector2f(std::cos(angle), std::sin(angle)) * distance;

	this->rectangePos.x += this->offsetX;
	this->rectangePos.y += this->offsetY;

	rectangle.setPosition(this->rectangePos);

	rectangle.setRotation(angle * 180 / PI);

	this->circle.setPosition(this->rectangle.getPosition().x, this->rectangle.getPosition().y);
}

void AimDirection::render(sf::RenderTarget& target)
{
	target.draw(this->rectangle);
	target.draw(this->circle);
}
