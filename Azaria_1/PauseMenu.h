#pragma once

#include"Gui.h"

class Gui;

class PauseMenu
{
private:
	// Variables
	sf::Font& font;
	sf::Text menuText;
	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, GUI::Button*> buttons;

public:
	// Constructor/Destructor
	PauseMenu(sf::VideoMode& vm, sf::Font& font);
	PauseMenu(sf::VideoMode& vm, sf::Font& font, std::string text, sf::Color color, bool horiz);
	virtual ~PauseMenu();

	//Functions
	std::map<std::string, GUI::Button*>& GetButtons();

	const bool IsButtonPressed(const std::string key);
	void AddButton(const std::string key, const float y, const float width, const float height, const unsigned charSize, const std::string text);
	void Update(const sf::Vector2i& mousePosWindow);
	void Render(sf::RenderTarget& target);
};

