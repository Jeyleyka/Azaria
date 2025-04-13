#include "stdafx.h"
#include "Enemy.h"

//Initializer functions
void Enemy::InitVariables()
{
	this->gainExp = 10;
	this->damageTimerMax = 1000;
	this->despawnTimerMax = 1000;

	if (!this->iceTexture.loadFromFile("Resources/Other/ice.png")) exit(8);
	this->iceSprite.setTexture(this->iceTexture);
	this->iceSprite.setColor(sf::Color(3, 29, 160, 150));
}

void Enemy::InitAnimations()
{

}

//Constructors / Destructors
Enemy::Enemy(EnemySpawnerTile& enemy_spawner_tile)
	: enemySpawnerTile(enemy_spawner_tile)
{
	this->InitVariables();
	this->InitAnimations();
}

Enemy::~Enemy()
{

}

const unsigned& Enemy::GetGainExp() const
{
	return this->gainExp;
}

EnemySpawnerTile& Enemy::GetEnemySpawnerTile()
{
	return this->enemySpawnerTile;
}

const bool& Enemy::GetCombustion() const
{
	return this->showComb;
}

const bool Enemy::GetDamageTimerDone() const
{
	return this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax;
}

const bool Enemy::GetDespawnTimerDone() const
{
	return this->despawnTimer.getElapsedTime().asMilliseconds() >= this->despawnTimerMax;
}

void Enemy::ResetDamageTimer()
{
	this->damageTimer.restart();
}

void Enemy::SetCombustion()
{
	//this->typeOfModidy = ModifyTypes::COMB;
	this->showComb = true;
}

void Enemy::SetModify(unsigned short mod)
{
	//this->typeOfModidy = ModifyTypes::COMB;
	this->typeOfModify = mod;
}

void Enemy::GenerateAttributes(const unsigned level)
{
	this->gainExp = level * (rand() % 5 + 1);
}

void Enemy::LoseHP(const float hp)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->LoseHP(hp);
	}
}

const bool Enemy::IsDead() const
{
	if (this->attributeComponent)
	{
		return this->attributeComponent->IsDead();
	}

	return false;
}

const AttributeComponent* Enemy::GetAttributeComponent() const
{
	if (this->attributeComponent)
		return this->attributeComponent;
	else
	{
		std::cout << "ERROR::ENEMY::ATTRIBUTECOMPONENT IS NOT INITIALIZED" << "\n";
		return nullptr;
	}
}

void Enemy::Update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view)
{
	if (VectorDistance(this->GetPosition(), view.getCenter()) < 15000.f)
		this->despawnTimer.restart();
}