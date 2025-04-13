#pragma once

#include"AnimationComponent.h"

class Coin
{
private:
	// Variables
	AnimationComponent* animationComponent;

	sf::Texture textureSheet;
	sf::Sprite shape;

	// Initializer functions
	void InitAnimation();
public:
	// Constructor/Desctructor
	Coin(float posX, float posY);
	~Coin();

	const sf::Vector2f GetCenter() const;
	const sf::FloatRect& GetGlobalBounds() const;

	void CreateAnimationComponent(sf::Texture& textureSheet);
	void SetScale(float x, float y);
	void SetPosition(float posX, float posY);
	void Update(const float& dt);
	void Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPosition);
};

