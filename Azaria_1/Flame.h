#pragma once

#include"AnimationComponent.h"

class Flame
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
	Flame();
	Flame(float posX, float posY);
	~Flame();

	const sf::Vector2f GetCenter() const;
	const sf::FloatRect& GetGlobalBounds() const;

	void CreateAnimationComponent(sf::Texture& textureSheet);
	void SetScale(float x, float y);
	void SetPosition(float posX, float posY);
	void SetPosition(sf::Vector2f& pos);
	void Update(const float& dt);
	void Render(sf::RenderTarget& target);
};

