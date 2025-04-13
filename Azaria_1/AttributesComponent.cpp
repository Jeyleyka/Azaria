#include "stdafx.h"
#include "AttributesComponent.h"

// Constructor/Destructor
AttributeComponent::AttributeComponent(int level)
{
	this->level = level;
	this->exp = 0;
	this->expNext = (50 * pow(this->level, 3) - 150 * pow(this->level, 2) + (UINT64)400 * this->level) / 3;
	this->attributePoints = 2;
	this->vitality = 1;
	this->strength = 1;
	this->dexterity = 1;
	this->agility = 1;
	this->intelligence = 1;
	this->damageStates = DEFAULT_ATTACK;

	this->UpdateLevel();
	this->UpdateStats(true);
}

AttributeComponent::~AttributeComponent()
{

}

std::string AttributeComponent::DebugPrint() const
{
	std::stringstream ss;

	ss << "Level: " << this->level << "\n"
		<< "Exp: " << this->exp << "\n"
		<< "Exp Next: " << this->expNext << "\n"
		<< "Attp: " << this->attributePoints << "\n";

	return ss.str();
}

// Functions
void AttributeComponent::LoseHP(const float hp)
{
	this->hp -= hp;

	if (this->hp < 0.f)
		this->hp = 0.f;
}

void AttributeComponent::LoseEXP(const int exp)
{
	this->exp -= exp;

	if (this->exp < 0)
		this->exp = 0;
}

void AttributeComponent::GainHP(const int hp)
{
	this->hp += hp;

	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void AttributeComponent::GainExp(const int exp)
{
	this->exp += exp;

	this->UpdateLevel();
}

const bool AttributeComponent::IsDead() const
{
	return this->hp <= 0;
}

void AttributeComponent::UpdateStats(const bool reset)
{
	this->hpMax = this->vitality * 5 + this->vitality + this->strength / 2 + this->intelligence / 5;

	this->damageStates = rand() % 8;

	if (this->damageStates == 0 || this->damageStates == 1 || this->damageStates == 2 || this->damageStates == 3 || this->damageStates == 4
		|| this->damageStates == 5)
	{
		this->damageStates = DEFAULT_ATTACK;
		this->damageMin = this->strength * 2 + this->strength / 4 + this->intelligence / 5;
		this->damageMax = this->strength * 2 + this->strength / 2 + this->intelligence / 5;
	}
	else if (damageStates == 6)
	{
		this->damageStates = DODGE;
		this->damageMax = 0;
		this->damageMin = 0;
	}
	else if (this->damageStates == 7 || this->damageStates == 8)
	{
		this->damageStates = CRIT;
		this->damageMin = this->strength * 6 + this->strength / 3 + this->intelligence / 5;
		this->damageMax = this->strength * 6 + this->strength / 3 + this->intelligence / 5;
	}

	this->accuracy = this->dexterity * 5 + this->dexterity / 2 + this->intelligence / 5;
	this->defence = this->agility * 2 + this->agility / 4 + this->intelligence / 5;
	this->luck = this->intelligence * 2 + this->intelligence / 5;

	if (reset)
		this->hp = this->hpMax;
}

void AttributeComponent::UpdateLevel()
{
	while (this->exp >= this->expNext)
	{
		++this->level;
		this->exp -= this->expNext;
		this->expNext = (50 * pow(this->level, 3) - 150 * pow(this->level, 2) + (UINT64)400 * this->level) / 3;
		++this->attributePoints;
	}
}

void AttributeComponent::Update()
{
	this->UpdateLevel();
}
