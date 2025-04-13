#pragma once

#include"State.h"
#include"TileMap.h"
#include"Gui.h"

class State;
class StateData;
class TileMap;
class Tile;

class EditorStateData
{
public:
	EditorStateData() {};

	// Variables
	sf::View* view;
	sf::Font* font;
	sf::Vector2i* mousePosScreen;
	sf::Vector2i* mousePosWindow;
	sf::Vector2f* mousePosView;
	sf::Vector2i* mousePosGrid;

	std::map<std::string, int>* keybinds;

	float* keytime;
	float* keytimeMax;
};

class EditorMode
{
private:

protected:
	// Variables
	StateData* stateData;
	EditorStateData* editorStateData;
	TileMap* tileMap;

public:
	// Constructor/Destructor
	EditorMode(StateData* stateData, TileMap* tileMap, EditorStateData* editorStateData);
	virtual ~EditorMode();

	// Functions
	const bool GetKeytime();
	virtual void UpdateInput(const float& dt) = 0;
	virtual void UpdateGui(const float& dt) = 0;
	virtual void Update(const float& dt) = 0;
	virtual void RenderGui(sf::RenderTarget& target) = 0;
	virtual void Render(sf::RenderTarget& target) = 0;
};

