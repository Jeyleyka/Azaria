#pragma once

#include"AnimationComponent.h"
#include"Player.h"

class Swordsmen : public Entity
{
private:
	// Variables
	AIFollow* follow;
	AnimationComponent* animationComponent;

	sf::Clock damageTimer;
	sf::Int32 damageTimerMax;

	bool openShop;

	// Initializer functions
	void InitAnimation();

public:
	// Constructor/Desctructor
	Swordsmen(float posX, float posY, sf::Texture& texture_sheet, Entity& Player);
	virtual ~Swordsmen();

	const sf::Vector2f& GetPosition() const;
	const sf::Vector2f GetCenter() const;
	const float GetDamage() const;
	const bool& GetDamageTimer();

	void CreateAnimationComponent(sf::Texture& textureSheet);
	void SetScale(float x, float y);
	void SetPosition(float posX, float posY);
	void UpdateAnimation(const float& dt);
	void CheckIsEnemiesInTileMap(Entity& Enemy);
	void Update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view);
	void Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPosition);
};

