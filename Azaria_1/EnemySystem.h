#pragma once

#include "EnemySpawnerTile.h"
#include"Enemies.h"

enum EnemyTypes { RAT = 0, BIRD, SPIDER, BLOB };

class EnemySystem
{
private:
	std::map<std::string, sf::Texture>& textures;
	std::vector<Enemy*>& activeEnemies;
	Entity& player;

public:
	EnemySystem(std::vector<Enemy*>& activeEnemies,
		std::map<std::string, sf::Texture>& textures, Entity& player);
	virtual ~EnemySystem();

	//Accessors

	//Modifiers

	//Functions
	void CreateEnemy(const short type, const float xPos, const float yPos, EnemySpawnerTile& enemy_spawner_tile);
	void RemoveEnemy(const int index);

	void Update(const float& dt);
	void Render(sf::RenderTarget* target);
};

