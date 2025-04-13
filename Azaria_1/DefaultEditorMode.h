#pragma once

#include "EditorMode.h"

class State;
class StateData;
class EditorMode;
class TileMap;
class Tile;

class DefaultEditorMode : public EditorMode
{
private:
	// Variables
	GUI::TextureSelector* textureSelector;
	GUI::Layout* layout;

	sf::RectangleShape selectorRect;
	sf::IntRect textureRect;
	sf::Text cursorText;
	sf::RectangleShape sidebar;

	bool collision;
	bool tileAddLock;
	int layer;
	short type;

	// Initialization
	void InitVariables();
	void InitGui();

public:
	// Constructor/Destructor
	DefaultEditorMode(StateData* stateData, TileMap* tileMap, EditorStateData* editorStateData);
	virtual ~DefaultEditorMode();

	// Functions
	void UpdateInput(const float& dt);
	void UpdateGui(const float& dt);
	void Update(const float& dt);
	void RenderGui(sf::RenderTarget& target);
	void Render(sf::RenderTarget& target);
};

