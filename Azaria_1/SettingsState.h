#pragma once

#include "State.h"

class SettingsState : public State
{
private:
	// Variables

	sf::Texture volumeTexture;
	sf::Sprite volumeSprite;
	sf::Music* music;
	sf::Texture bgTex;
	sf::RectangleShape background;
	sf::Font font;
	sf::Font specialFont;
	sf::RectangleShape volumeBack;
	sf::RectangleShape volumeInner;
	sf::Text optionsText;

	std::map<std::string, GUI::Button*> buttons;
	std::map<std::string, GUI::DropDownList*> resolutionList;
	std::map<std::string, GUI::DropDownList*> fullscreanList;
	std::vector<sf::VideoMode> modes;
	std::vector<std::string> fullscrean;

	// Initialization
	void InitVariables();
	void InitFonts();
	void InitValue();
	void InitKeybinds();
	void InitGui();
	void ResetGui();

public:

	// Constructor/Destructor
	SettingsState(sf::Music* music, StateData* stateData);
	virtual ~SettingsState();

	// Functions
	void UpdateInput(const float& dt);
	void UpdateVolume(sf::Music* music, float volumeChange);
	void UpdateGui(const float& dt);
	void Update(sf::Music* music, const float& dt);
	void RenderGui(sf::RenderTarget& target);
	void RenderValue(sf::RenderTarget& target);
	void Render(sf::RenderTarget* target = NULL);
};

