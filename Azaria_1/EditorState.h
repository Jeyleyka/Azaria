#pragma once

#include "State.h"
#include"Gui.h"
#include"PauseMenu.h"
#include"TileMap.h"
#include"EditorModes.h"

class State;
class StateData;
class PauseMenu;
class TileMap;
class Tile;
class EditorMode;
class DefaultEditorMode;
class EditorStateData;
class EnemyEditorMode;

enum EditorModes { DEFAULT_EDITOR_MODE = 0, ENEMY_EDITOR_MODE };

class EditorState : public State
{
private:
	// Variables
	EditorStateData editorStateData;
	PauseMenu* pmenu;
	TileMap* tileMap;

	sf::View view;
	sf::Font font;

	std::map<int, std::string> layoutMap;
	std::map<std::string, GUI::Button*> buttons;
	std::vector<EditorMode*> modes;

	unsigned activeMode;
	float cameraSpeed;

	// Initialization
	void InitVariables();
	void InitEditorStateData();
	void InitView();
	void InitFonts();
	void InitKeybinds();
	void InitPauseMenu();
	void InitLayoutMap();
	void InitButtons();
	void InitGui();
	void InitTileMap();
	void InitModes();

public:
	// Constructor/Destructor
	EditorState(StateData* stateData);
	virtual ~EditorState();

	// Functions
	void UpdateInput(const float& dt);
	void UpdateEditorInput(const float& dt);
	void UpdateButtons();
	void UpdateGui(const float& dt);
	void UpdatePauseMenuButtons();
	void UpdateModes(const float& dt);
	void Update(sf::Music* music, const float& dt);
	void RenderButtons(sf::RenderTarget& target);
	void RenderGui(sf::RenderTarget& target);
	void RenderModes(sf::RenderTarget& target);
	void Render(sf::RenderTarget* target = NULL);
};

