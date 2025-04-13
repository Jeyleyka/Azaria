#pragma once

#include"AnimationComponent.h"

class FireShot
{
private:
	// Variables
	AnimationComponent* animationComponent;

	sf::Texture textureSheet;
	sf::Sprite shape;
	sf::Vector2f velocity;

	float animationTime; 
	float offsetX;
	float offsetY;
	size_t currentFrame;

	bool explosion;
	bool isShooting;
	bool isDrawingTrajectory;

	// Initializer functions
	void InitAnimation();

public:
	// Constructor/Desctructor
	FireShot(float posX, float posY, float angle);
	~FireShot();

	const sf::Vector2f GetCenter() const;
	const sf::FloatRect& GetGlobalBounds() const;

	void CreateAnimationComponent(sf::Texture& textureSheet);
	void SetScale(float x, float y);
	void SetPosition(float posX, float posY);
	void Update(const float& dt);
	void Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPosition);
};

