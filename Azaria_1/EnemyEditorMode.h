#pragma once
#include "EditorMode.h"
#include "EnemySpawnerTile.h"

class State;
class StateData;
class EditorMode;
class TileMap;
class Tile;
class EnemySpawner;

class EnemyEditorMode : public EditorMode
{
private:
	// Variables
	sf::Text cursorText;
	sf::RectangleShape sidebar;
	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;

	int amount;
	int timeToSpawn;
	float maxDistance;
	short type;

	// Initializer functions
	void InitVariables();
	void InitGui();

public:
	// Constructor/Destructor
	EnemyEditorMode(StateData* stateData, TileMap* tileMap, EditorStateData* editorStateData);
	virtual ~EnemyEditorMode();

	// Functions
	void UpdateInput(const float& dt);
	void UpdateGui(const float& dt);
	void Update(const float& dt);
	void RenderGui(sf::RenderTarget& target);
	void Render(sf::RenderTarget& target);
};

