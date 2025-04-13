#pragma once

#include"Player.h"
#include"GUI.h"

class Player;
class Gui;
class sf::RectangleShape;

class PlayerGUI
{
private:
	// Variables
	Player* player;
	GUI::ProgressBar* hpBar;
	GUI::ProgressBar* expBar;
	GUI::Button* inventory;

	sf::VideoMode& vm;
	sf::Font font;
	sf::Texture inventoryTexture;

	std::string levelBarString;
	sf::Text levelBarText;
	sf::RectangleShape levelBarBack;

	//Initializer functions
	void InitFont();
	void InitLevelBar();
	void InitEXPBar();
	void InitHPBar();
	void InitInventory();

public:
	// Constructor/Destructor
	PlayerGUI(Player* player, sf::VideoMode& vm);
	virtual ~PlayerGUI();

	// Functions
	void UpdateLevelBar();
	void UpdateEXPBar();
	void UpdateHPBar();
	void UpdateInventory();

	void Update(const float& dt);
	void RenderLevelBar(sf::RenderTarget& target);
	void RenderEXPBar(sf::RenderTarget& target);
	void RenderHPBar(sf::RenderTarget& target);
	void RenderInventory(sf::RenderTarget& target);
	void Render(sf::RenderTarget& target);
};

