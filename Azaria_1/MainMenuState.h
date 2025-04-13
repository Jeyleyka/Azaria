#pragma once

#include"ArcadaState.h"
#include"EditorState.h"
#include"SettingsState.h"
#include"LevelsState.h"
#include"Player.h"

class MainMenuState : public State
{
private:
	// Variables
	Player* player;
	SettingsState* settingsState;
	PauseMenu* pmenu;

	sf::SoundBuffer buffer;
	sf::Music music;
	sf::Texture bgTex;
	sf::RectangleShape background;
	sf::Font font;
	sf::Font specialFont;
	sf::Text bestScore;

	std::vector<LevelsState*> levels;
	std::vector<sf::VideoMode> modes;
	std::map<std::string, GUI::DropDownList*> resolutionList;
	std::map<std::string, GUI::Button*> buttons;

	float score;

	int loadLevel;
	bool isSet;

	// Initialization
	void InitVariables();
	void InitLevel(const std::string file_name);
	void InitMusic();
	void InitFonts();
	void InitKeybinds();
	void InitBestScore();
	void InitGui();
	void ResetGui();

public:
	// Constructor/Destructor
	MainMenuState(StateData* stateData);
	virtual ~MainMenuState();

	// Functions
	void UpdateInput(const float& dt);
	void UpdateButtons(const float& dt, std::string file_name);
	void UpdateMusic();
	void Update(sf::Music* music, const float& dt);
	void RenderButtons(sf::RenderTarget& target);
	void Render(sf::RenderTarget* target = NULL);
};

