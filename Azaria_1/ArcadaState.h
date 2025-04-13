#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "Rat.h"
#include "TextTagSystem.h"
#include"Weapon.h"

class ArcadaState : public State
{
private:
	// Variables
	Weapon* weapon;
	PauseMenu* pmenu;
	PauseMenu* diedMenu;
	Player* player;
	PlayerGUI* playerGUI;
	EnemySystem* enemySystem;
	TileMap* tileMap;
	TextTagSystem* textTagSystem;

	sf::Sprite inventorySprite;
	sf::Texture inventoryTexture;
	sf::RectangleShape inventory;
	sf::Text score;
	sf::Clock time;
	sf::Vector2i viewGridPosition;
	sf::Font font;
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;
	sf::Shader coreShader;
	sf::Text debugText;
	sf::Clock keyTimer;
	sf::Text gameTimerText;

	std::vector<Enemy*> activeEnemies;

	float keyTimeMax;

	// Initialization
	void InitDeferredRender();
	void InitView();
	void InitKeybinds();
	void InitFonts();
	void InitTextures();
	void InitGameTimer();
	void InitDebugText();
	void InitPauseMenu();
	void InitDiedMenu();
	void InitKeyTime();
	void InitShaders();
	void InitPlayers();
	void InitPlayerGUI();
	void InitEnemySystem();
	void InitTileMap();
	void InitSystems();

public:
	// Constructor/Destructor
	ArcadaState(StateData* stateData);
	virtual ~ArcadaState();

	// Functions
	const bool GetKeyTime();
	void UpdateView(const float& dt);
	void UpdateInput(const float& dt);
	void UpdatePlayerInput(const float& dt);
	void UpdatePlayerGUI(const float& dt);
	void UpdatePauseMenuButtons();
	void UpdateDiedMenuButtons();
	void UpdateTileMap(const float& dt);
	void UpdatePlayer(const float& dt);
	void UpdateGameTimer();
	void UpdateCombatAndEnemies(const float& dt);
	void UpdateCombat(Enemy* enemy, const int index, const float& dt);
	void UpdateDebugText(const float& dt);
	void RecordBestTime();
	void Update(sf::Music* music, const float& dt);
	void Render(sf::RenderTarget* target = NULL);
};

