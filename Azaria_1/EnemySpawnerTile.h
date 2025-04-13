#pragma once

#include "Tile.h"

class Tile;

class EnemySpawnerTile : public Tile
{
private:
	// Variables
	sf::Int32 enemyTimeToSpawn;
	sf::Clock enemySpawnTimer;
	float enemyMaxDistance;
	int enemyCounter;
	int enemyType;
	int enemyAmount;
	bool firstSpawned;

public:
	// Constructor/Destructor
	EnemySpawnerTile(int x, int y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& textureRect, int enemyType,
		int enemyAmount, sf::Int32 enemyTimeToSpawn, float enemyMaxDistance);
	virtual ~EnemySpawnerTile();

	// Functions
	const std::string GetAsString() const;
	const int& GetEnemyCounter() const;
	const int& GetEnemyAmount() const;
	const bool GetSpawnTimer();
	const int& GetEnemyType() const;
	const float& GetEnemyMaxDistance() const;
	void IncreaseEnemyCounter();
	void DecreaseEnemyCounter();
	void Update();
	void Render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f playerPosition = sf::Vector2f());
};

