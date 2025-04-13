#include "stdafx.h"
#include "EnemySpawnerTile.h"

EnemySpawnerTile::EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF,
	const sf::Texture& texture, const sf::IntRect& texture_rect,
	int enemy_type, int enemy_amount, sf::Int32 enemy_time_to_spawn, float enemy_max_distance)

	: Tile(TileTypes::ENEMYSPAWNER, grid_x, grid_y, gridSizeF, texture, texture_rect, false)
{
	this->enemyType = enemy_type;
	this->enemyAmount = enemy_amount;
	this->enemyCounter = 0;
	this->enemySpawnTimer.restart();
	this->enemyTimeToSpawn = enemy_time_to_spawn;
	this->enemyMaxDistance = 150000.f;
	this->firstSpawned = true;
}

EnemySpawnerTile::~EnemySpawnerTile()
{

}

const std::string EnemySpawnerTile::GetAsString() const
{
	std::stringstream ss;

	/*
	x, y, z (done in tilemap save)
	type,
	rect x, rect y,
	enemy type,
	enemy amount
	enemy time to spawn
	enemy max distance
	*/

	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " "
		<< this->enemyType << " " << this->enemyAmount << " " << this->enemyTimeToSpawn << " " << this->enemyMaxDistance;

	//std::cout << ss.str() << "\n";

	return ss.str();
}

const int& EnemySpawnerTile::GetEnemyAmount() const
{
	return this->enemyAmount;
}

const int& EnemySpawnerTile::GetEnemyCounter() const
{
	return this->enemyCounter;
}

const bool EnemySpawnerTile::GetSpawnTimer()
{
	if (this->enemySpawnTimer.getElapsedTime().asSeconds() >= this->enemyTimeToSpawn || this->firstSpawned)
	{
		this->enemySpawnTimer.restart();
		this->firstSpawned = false;
		return true;
	}

	return false;
}

const int& EnemySpawnerTile::GetEnemyType() const
{
	return this->enemyType;
}

const float& EnemySpawnerTile::GetEnemyMaxDistance() const
{
	return this->enemyMaxDistance;
}

void EnemySpawnerTile::IncreaseEnemyCounter()
{
	if (this->enemyCounter < this->enemyAmount)
		++this->enemyCounter;
}

void EnemySpawnerTile::DecreaseEnemyCounter()
{
	if (this->enemyCounter > 0)
		--this->enemyCounter;
}

//Functions
void EnemySpawnerTile::Update()
{

}

void EnemySpawnerTile::Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_position)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", player_position);

		target.draw(this->shape, shader);
	}
	else
		target.draw(this->shape);
}