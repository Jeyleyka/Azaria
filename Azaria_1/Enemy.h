#pragma once
#include "Entity.h"
#include"AIFollow.h"
#include"EnemySpawnerTile.h"

class Enemy : public Entity
{
protected:
	// Variables

	EnemySpawnerTile& enemySpawnerTile;

	sf::Sprite iceSprite;
	sf::Texture iceTexture;
	sf::Clock damageTimer;
	sf::Int32 damageTimerMax;
	sf::Clock despawnTimer;
	sf::Int32 despawnTimerMax;

	unsigned gainExp;

	bool combustion;
	bool showComb;
	bool showFreez;

	//Initialize functions
	virtual void InitVariables();
	virtual void InitAnimations();

public:
	// Constructor/Destructor
	Enemy(EnemySpawnerTile& enemySpawnerTile);
	virtual ~Enemy();

	// Functions
	const unsigned& GetGainExp() const;
	EnemySpawnerTile& GetEnemySpawnerTile();
	const bool& GetCombustion() const;
	const bool GetDamageTimerDone() const;
	const bool GetDespawnTimerDone() const;
	void ResetDamageTimer();
	void SetCombustion();
	void SetModify(unsigned short mod);
	virtual void GenerateAttributes(const unsigned level);
	virtual void LoseHP(const float hp);
	virtual const bool IsDead() const;
	virtual const AttributeComponent* GetAttributeComponent() const;
	virtual void UpdateAnimation(const float& dt) = 0;
	virtual void Update(const float& dt, sf::Vector2f& mousePosView, const sf::View& view);
	virtual void Render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f lightPosition = sf::Vector2f()) = 0;
};

