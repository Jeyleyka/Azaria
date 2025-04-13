#pragma once

#include"Player.h"
#include"Gui.h"
#include"GraphicSettings.h"

class Player;
class Gui;
class GraphicsSettings;
class State;

class StateData
{
public:
	StateData() {};

	// Variables
	GraphicSettings* gfxSettings;

	sf::RenderWindow* window;

	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;

	float gridSize;
};

class State
{
private:

protected:
	// Variables
	StateData* stateData;

	sf::Music* music;
	sf::RenderWindow* window;
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;
	sf::Time gameTimer;
	sf::Clock gameClock;

	std::stack<State*>* states;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	std::map<std::string, sf::Texture> textures;

	bool quit;
	bool paused;
	bool died;
	bool showed;
	bool isOpen;
	bool newLevel;
	bool hideChest;
	bool loading;
	bool enemiesIsDead;
	bool showCoin;
	float keytime;
	float keytimeMax;
	float gridSize;

	int currentLevel;

	// Initialization
	virtual void InitKeybinds() = 0;

public:
	// Constructor/Destructor
	State(StateData* stateData, sf::Music* music = NULL);
	virtual ~State();

	// Functions
	//const int& GetNumberDiedEnemies() const;
	const bool& GetQuit() const;
	const bool GetKeytime();
	void EndState();
	void ShowedState();
	void UnshowedState();
	void PauseState();
	void UnpauseState();
	void PlayerDied();
	void UpdateLevel();
	void IsOpen();
	void Close();

	virtual void UpdateMousePositions(sf::View* view = NULL);
	virtual void Updatekeytime(const float& dt);
	virtual void UpdateInput(const float& dt) = 0;
	virtual void Update(sf::Music* music, const float& dt) = 0;
	virtual void Render(sf::RenderTarget* target = NULL) = 0;
};

