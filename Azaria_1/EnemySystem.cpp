#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies,
	std::map<std::string, sf::Texture>& textures, Entity& player)
	: textures(textures), activeEnemies(activeEnemies), player(player)
{

}

EnemySystem::~EnemySystem()
{

}

void EnemySystem::CreateEnemy(const short type, const float xPos, const float yPos, EnemySpawnerTile& enemy_spawner_tile)
{
	switch (type)
	{
	case EnemyTypes::RAT:
		this->activeEnemies.push_back(new Rat(xPos, yPos, this->textures["RAT1_SHEET"], enemy_spawner_tile, this->player));
		enemy_spawner_tile.IncreaseEnemyCounter();
		break;
	case EnemyTypes::BIRD:
		this->activeEnemies.push_back(new Bird(xPos, yPos, this->textures["BIRD1_SHEET"], enemy_spawner_tile, this->player));
		enemy_spawner_tile.IncreaseEnemyCounter();
		break;

	case EnemyTypes::SPIDER:
		this->activeEnemies.push_back(new Spider(xPos, yPos, this->textures["SPIDER_SHEET"], enemy_spawner_tile, this->player));
		enemy_spawner_tile.IncreaseEnemyCounter();
		break;

	case EnemyTypes::BLOB:
		this->activeEnemies.push_back(new Spider(xPos, yPos, this->textures["BLOB_SHEET"], enemy_spawner_tile, this->player));
		enemy_spawner_tile.IncreaseEnemyCounter();
		break;

	default:
		std::cout << "ERROR::ENEMYSYSTEM::CREATEENEMY::TYPE DOES NOT EXIST" << "\n";
		break;
	}
}

void EnemySystem::RemoveEnemy(const int index)
{
	this->activeEnemies[index]->GetEnemySpawnerTile().DecreaseEnemyCounter();
	delete this->activeEnemies[index];
	this->activeEnemies.erase(this->activeEnemies.begin() + index);
}

void EnemySystem::Update(const float& dt)
{

}

void EnemySystem::Render(sf::RenderTarget* target)
{

}