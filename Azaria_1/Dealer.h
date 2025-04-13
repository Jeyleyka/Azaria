#pragma once

#include"AnimationComponent.h"

class Dealer
{
private:
	// Variables
	AnimationComponent* animationComponent;

	sf::Font font;
	sf::Texture textureSheet;
	sf::Sprite shape;
	sf::RectangleShape greetingBg;
	sf::Text greetingText;
	sf::Text pressButton;

	bool openShop;

	// Initializer functions
	void InitAnimation();

public:
	// Constructor/Desctructor
	Dealer(float posX, float posY, float greetingPosX, float greetingPosY);
	~Dealer();

	const sf::Vector2f& GetPosition() const;
	const sf::Vector2f& GetCenter() const;
	const sf::FloatRect& GetGlobalBounds() const;

	void CreateAnimationComponent(sf::Texture& textureSheet);
	void SetScale(float x, float y);
	void SetPosition(float posX, float posY);
	void SetShopTrue();
	void SetShopFalse();
	void Update(const float& dt);
	void Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPosition);
};

