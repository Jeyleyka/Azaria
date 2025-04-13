#pragma once

#include "Enemy.h"
#include "Flame.h"

class Blob :
	public Enemy
{
private:
	void InitVariables();
	void InitAnimations();
	void InitAI();
	void InitGUI();

	Flame* flame;
	AIFollow* follow;

	sf::RectangleShape hpBar;

public:
	Blob(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player);
	virtual ~Blob();

	//Functions
	void UpdateAnimation(const float& dt);
	void Update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view);

	void Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position);
};