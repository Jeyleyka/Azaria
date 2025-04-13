#include "stdafx.h"
#include "Sword.h"

Sword::Sword(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string textureFile, unsigned short modify)
	: MeleeWeapon(level, damageMin, damageMax, range, value, textureFile)
{
	this->weaponTexture.loadFromFile(textureFile);
	this->weaponSprite.setTexture(this->weaponTexture);
	this->weaponSprite.setOrigin(this->weaponSprite.getGlobalBounds().width / 2.f, this->weaponSprite.getGlobalBounds().height);
}

Sword::~Sword()
{
}

Sword* Sword::Clone()
{
	return new Sword(*this);
}

void Sword::Update(const sf::Vector2f& mousePosView, const sf::Vector2f center, const sf::View& view)
{
	this->weaponSprite.setPosition(center);

	float dX = mousePosView.x - this->weaponSprite.getPosition().x;
	float dY = mousePosView.y - this->weaponSprite.getPosition().y;

	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->attackTimer.getElapsedTime().asMilliseconds() < this->attackTimerMax / 3)
		this->weaponSprite.setRotation(this->weaponSprite.getRotation() + 6.f);
	else
		this->weaponSprite.setRotation(deg + 90.f);
}

void Sword::Render(sf::RenderTarget& target, sf::Shader* shader)
{
	if (shader)
		target.draw(this->weaponSprite, shader);
	else
		target.draw(this->weaponSprite);
}
