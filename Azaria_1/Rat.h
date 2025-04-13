#pragma once

#include "Enemy.h"
#include "Flame.h"

class Rat : public Enemy
{
private:
	// Variables

	//Initializer functions
	void InitVariables();
	void InitAnimations();
	void InitAI();
	void InitGUI();

	Flame* flame;
	AIFollow* follow;

	sf::RectangleShape hpBar;

public:
	// Constructor/Destructor
	Rat(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemySpawnerTile, Entity& player);
	virtual ~Rat();

	// Functions
	void UpdateAnimation(const float& dt);
	void Update(const float& dt, sf::Vector2f& mousePosView, const sf::View& view);
	void Render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f lightPosition = sf::Vector2f());
};

