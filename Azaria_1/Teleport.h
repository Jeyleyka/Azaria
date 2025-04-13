#pragma once

#include"AnimationComponent.h"

class Teleport
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
	Teleport(float posX, float posY);
	~Teleport();

	const sf::Vector2f GetCenter() const;
	const sf::FloatRect& GetGlobalBounds() const;

	void CreateAnimationComponent(sf::Texture& textureSheet);
	void SetPosition(float posX, float posY);
	void Update(const float& dt);
	void Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPosition);
};

