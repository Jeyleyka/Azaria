#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "Rat.h"
#include "TextTagSystem.h"
#include"Weapon.h"
#include"Chest.h"
#include"Objects.h"
#include"Shop.h"
#include"FireShot.h"
#include"Swordsmen.h"
#include"AimDirection.h"

enum SwordModifiers {NO, FLAME, ICE};

class LevelsState : public State
{
private:
	// Variables
	Swordsmen* swordsmen;
	FireShot* fireShot;
	Shop* shop;
	Dealer* dealer;
	Coin* coin;
	Teleport* teleport;
	Weapon* weapon;
	PauseMenu* pmenu;
	PauseMenu* diedMenu;
	Player* player;
	PlayerGUI* playerGUI;
	EnemySystem* enemySystem;
	TileMap* tileMap;
	TextTagSystem* textTagSystem;
	Chest* chest;
	AimDirection* aimDir;

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
	sf::Clock keyTimer;
	sf::Sprite newWeapon;
	sf::Texture newWeaponTexture;
	sf::Text newWeaponText;
	sf::Clock endLevelTimer;
	sf::Text endLevelText;
	sf::RectangleShape loadingShape;
	sf::Text loadingText;
	sf::Clock loadingClock;
	sf::RectangleShape loadingBack;
	sf::RectangleShape loadingInner;
	sf::Text showCountOfCoins;

	std::vector<Enemy*> activeEnemies;
	std::vector<Coin*> coins;
	std::vector<FireShot*> fireShots;
	std::thread swordsmenThread;

	float keyTimeMax;
	float loadTime;

	unsigned short swordModify;

	int beforeLevel;
	int countOfCoins;
	int result;

	bool updateLevel;
	bool showNewWeapon;
	bool buy;
	bool openShop;
	bool shot;
	bool buySwordsmen;
	bool showAimDir;

	//bool hideChest;

	// Initialization
	void InitDeferredRender();
	void InitView();
	void InitKeybinds();
	void InitLevel(const std::string file_name);
	void InitFonts();
	void InitTextures();
	void InitPauseMenu();
	void InitDiedMenu();
	void InitKeyTime();
	void InitShaders();
	void InitPlayers();
	void InitPlayerGUI();
	void InitEnemySystem();
	void InitTileMap(const std::string file_name);
	void InitSystems();
	void InitDealer();
	void InitCoin();
	void InitTeleport();
	void InitChest();
	void InitEndLevelTimer();
	void InitLoading();
	void InitShop();
	void InitFireShot();
	void InitSwordsmen();
	void initAimDir();

public:
	// Constructor/Destructor
	LevelsState(StateData* stateData, int currentLevel);
	virtual ~LevelsState();

	// Functions
	const bool& GetUpdateLevel() const;
	const bool GetKeyTime();
	const bool& GetHideChest() const;
	sf::Vector2f getRotatedCenter(const sf::RectangleShape& rectangle);
	void GoToTeleport();
	void UpdateView(const float& dt);
	void UpdateInput(const float& dt);
	void UpdatePlayerInput(const float& dt);
	void UpdatePlayerGUI(const float& dt);
	void UpdatePauseMenuButtons();
	void UpdateDiedMenuButtons();
	void UpdateTileMap(const float& dt);
	void UpdatePlayer(const float& dt);
	void UpdateCombatAndEnemies(const float& dt);
	void UpdateCombat(Enemy* enemy, const int index, const float& dt);
	void UpdateChest();
	void UpdateEndLevelTimer();
	void UpdateLoading();
	void UpdateTeleport();
	void UpdateLoadingBar();
	void UpdateCountEnemies();
	void UpdateRecordLevelInFile();
	void PickUpCoin();
	void UpdateShop();
	void updateAimDir();
	void Update(sf::Music* music, const float& dt);
	void Render(sf::RenderTarget* target = NULL);
};

