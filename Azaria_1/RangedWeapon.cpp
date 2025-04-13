#include "stdafx.h"
#include "RangedWeapon.h"

RangedWeapon::RangedWeapon(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string textureFile)
	: Weapon(level, damageMin, damageMax, range, value, textureFile)
{
	this->type = ItemTypes::IT_RANGEDWEAPON;
}

RangedWeapon::~RangedWeapon()
{
}

void RangedWeapon::Generate(const unsigned levelMax, const unsigned levelMin)
{
	this->level = rand() % (levelMax - levelMin + 1) + levelMin;

	this->damageMin = this->level * (rand() % 2 + 1);
	this->damageMax = this->level * (rand() % 2 + 1) + this->damageMin;

	this->range = this->level + rand() % 10 + 50;

	this->value = this->level + this->damageMin + this->damageMax + this->range + (rand() % level * 10);
}
