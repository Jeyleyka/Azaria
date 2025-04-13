#pragma once

#include"GUI.h"

class Shop
{
private:
	// Variables
	sf::Font font;
	sf::RectangleShape shopBg;
	sf::Text shop;

	std::vector<GUI::Card*> cards;

public:
	// Constructor/Destructor
	Shop(unsigned width, unsigned height, int level, const sf::VideoMode& vm);
	~Shop();

	const std::vector<GUI::Card*> GetArrayCards() const;
	const sf::Vector2f& GetCenter() const;

	void Update(const sf::Vector2f& mousePosView);
	void Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPosition);
};

