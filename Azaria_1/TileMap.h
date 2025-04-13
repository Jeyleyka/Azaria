#pragma once

#include"Player.h"
#include"State.h"
#include"RegularTile.h"
#include"EnemySpawnerTile.h"
#include"EnemySystem.h"

class Tile;
class RegularTile;
class Entity;
class EnemySpawnerTile;
class Enemy;
class Rat;

class TileMap
{
private:
	// Variables
	sf::Vector2i maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;

	std::vector<std::vector<std::vector<std::vector<Tile*>>>> map;
	std::string textureFile;
	std::stack<Tile*> defferedRenderStack;

	float gridSizeF;
	int fromX;
	int fromY;
	int toX;
	int toY;
	int layer;
	int gridSizeI;
	int layers;
	int numberDiedEnemies;

public:
	// Constructor/Destructor
	TileMap(float gridSize, int width, int height, std::string textureFile);
	TileMap(const std::string fileName);
	virtual ~TileMap();

	// Functions
	const bool TileEmpty(const int x, const int y, const int z) const;
	const int& GetNumberDiedEnemies() const;
	const sf::Texture* GetTileSheet() const;
	const int GetLayerSize(const int x, const int y, const int layer) const;
	const sf::Vector2i& GetMaxSizeGrid() const;
	const sf::Vector2f& GetMaxSizeF() const;

	void SetNumberDiedEnemies();
	void Clear();
	void AddTile(const int x, const int y, const int z, const sf::IntRect& textureRect, const bool& collision, const short& type);
	void AddTile(const int x, const int y, const int z, const sf::IntRect& textureRect, const int enemyType, const int enemyAmount,
		const int enemyTimeToSpawn, float enemyMaxDistance);
	void RemoveTile(const int x, const int y, const int z, const short = -1);

	void SaveToFile(const std::string path);
	void LoadFromFile(const std::string path);
	const bool CheckType(const int x, const int y, const int z, const short type) const;

	void UpdateWorldBoundsCollision(Entity* entity, const float& dt);
	void UpdateTileCollision(Entity* entity, const float& dt);
	void UpdateTiles(Entity* entity, const float& dt, EnemySystem& enemySystem);
	void Update(Entity* entity, const float& dt);
	void Render(sf::RenderTarget& target, const sf::Vector2i& gridPosition, sf::Shader* shader = NULL, const sf::Vector2f playerPosition = sf::Vector2f(), const bool show_collision = true);
	void DefferedRender(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f playerPosition = sf::Vector2f());
};

