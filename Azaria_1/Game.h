#pragma once
#include"MainMenuState.h"

class Game
{
private:
	// Variables
	GraphicSettings gfxSettings;
	StateData stateData;

	sf::Music music;
	sf::RenderWindow* window;
	sf::Event event;
	sf::Clock dtClock;

	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;

	float dt;
	float gridSize;

	// Initialization
	void InitVariables();
	void InitGraphicsSettings();
	void InitWindow();
	void InitKeys();
	void InitStateData();
	void InitStates();

public:
	// Constructor/Destructor
	Game();
	virtual ~Game();

	// Functions
	void EndApplication();
	void UpdateDt();
	void UpdateSFMLEvents();
	void Update();
	void Render();
	void Run();
};

