#include "stdafx.h"
#include "Weapon.h"

void Weapon::InitVariables()
{
	this->dodge = false;
	this->range = 1500;
	this->damageMin = 1;
	this->damageMax = 2;
	this->keytime = 0.f;
	this->keytimeMax = 10.f;

	this->attackTimer.restart();
	this->attackTimerMax = 500;
}

Weapon::Weapon(unsigned level, unsigned value, std::string textureFile)
	: Item(level, value)
{
	this->InitVariables();

	this->weaponTexture.loadFromFile(textureFile);

	this->weaponSprite.setTexture(this->weaponTexture);
}

Weapon::Weapon(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string textureFile, unsigned short modify)
	:Item(level, value)
{
	this->InitVariables();

	this->damageMin = damageMin;
	this->damageMax = damageMax;
	this->range = 1500;

	if (!this->weaponTexture.loadFromFile(textureFile)) exit(77);

	this->weaponSprite.setTexture(this->weaponTexture);
}

Weapon::~Weapon()
{
}

const bool Weapon::GetKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

const unsigned& Weapon::GetDamageMin() const
{
	return this->damageMin;
}

const unsigned& Weapon::GetDamageMax() const
{
	return this->damageMax;
}

const unsigned Weapon::GetDamage() const
{
	return rand() % (this->damageMax - this->damageMin + 1) + (this->damageMin);
}

// Functions
const unsigned Weapon::GetRange() const
{
	return this->range;
}

const unsigned short& Weapon::GetModifiers() const
{
	return this->typeModify;
}

const sf::FloatRect& Weapon::GetGlobalBoundsArrow() const
{
	for (size_t i = 0; i < this->arrows.size(); i++)
	{
		return this->arrows[i].shape.getGlobalBounds();
	}
}

const std::vector<Arrow>& Weapon::GetArrowArray() const
{
	return this->arrows;
}

bool Weapon::GetIntersectWithEnemy(Enemy* enemy)
{
	for (size_t i = 0; i < this->arrows.size(); i++)
	{
		if (this->arrows[i].shape.getGlobalBounds().intersects(enemy->GetGlobalBounds()))
			return true;
	}

	return false;
}

void Weapon::SetRange(unsigned range)
{
	this->range = range;
}

void Weapon::SetModifier(unsigned short modify)
{
	this->typeModify = modify;
}

void Weapon::RemoveArrow()
{
	for (size_t i = 0; i < this->arrows.size(); i++)
	{
		this->arrows.erase(this->arrows.begin() + i);
	}
}

const bool Weapon::GetAttackTimer()
{
	if (this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax)
	{
		this->attackTimer.restart();
		return true;
	}
	return false;
}
