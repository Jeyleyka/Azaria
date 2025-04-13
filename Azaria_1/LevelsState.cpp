#include"stdafx.h"
#include "LevelsState.h"

void LevelsState::InitDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0,
			0,
			this->stateData->gfxSettings->resolution.width,
			this->stateData->gfxSettings->resolution.height
		)
	);
}

//Initializer functions
void LevelsState::InitView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width) / 1.3f,
			static_cast<float>(this->stateData->gfxSettings->resolution.height) / 1.3f
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
			static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
		)
	);
}

void LevelsState::InitKeybinds()
{
	std::ifstream ifs("Config/gamestate_key.txt");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void LevelsState::InitPlayers()
{
	this->player = new Player(220, 220, this->textures["PLAYER_SHEET"], this->stateData->gfxSettings->resolution);
	this->swordModify = SwordModifiers::NO;
}

void LevelsState::InitLevel(const std::string file_name)
{
	std::ifstream in_file;

	in_file.open(file_name);

	if (in_file.is_open())
	{
		in_file >> this->beforeLevel;
		//std::cout << "Current level is update\n";
	}
	else
		std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILENAME: " << file_name << "\n";

	this->player->SetCurrentLevel(this->beforeLevel);

	this->player->SetNewLevel(this->player->GetCurrentLevel());

	in_file.close();
}

void LevelsState::InitFonts()
{
	if (!this->font.loadFromFile("Fonts/font3.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void LevelsState::InitTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Sprites/Player/player-test.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}

	if (!this->textures["RAT1_SHEET"].loadFromFile("Resources/Sprites/Enemy/rat.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_RAT1_TEXTURE";
	}

	if (!this->textures["BIRD1_SHEET"].loadFromFile("Resources/Sprites/Enemy/bird.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
	}

	if (!this->textures["CHEST"].loadFromFile("Resources/Other/box.png")) exit(05);

	if (!this->textures["SPIDER_SHEET"].loadFromFile("Resources/Sprites/Enemy/spider.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_SPIDER_TEXTURE";
	}

	if (!this->textures["BLOB_SHEET"].loadFromFile("Resources/Sprites/Enemy/blob.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BLOB_TEXTURE";
	}

	if (!this->textures["SWORDSMEN_SHEET"].loadFromFile("Resources/Sprites/Swordsmen/swordsmen.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
}

void LevelsState::InitPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->AddButton("QUIT", GUI::p2pY(74.f, vm), GUI::p2pX(13.f, vm), GUI::p2pY(6.f, vm), GUI::calcCharSize(vm), "Quit");
	this->pmenu->AddButton("SAVE", GUI::p2pY(24.f, vm), GUI::p2pX(13.f, vm), GUI::p2pY(6.f, vm), GUI::calcCharSize(vm), "Save");
}

void LevelsState::InitDiedMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->diedMenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font, "YOU DEAD!", sf::Color::Red, true);

	this->diedMenu->AddButton("MENU", GUI::p2pY(50.f, vm), GUI::p2pX(13.f, vm), GUI::p2pY(6.f, vm), GUI::calcCharSize(vm), "Menu");

}

void LevelsState::InitShaders()
{
	if (!this->coreShader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER." << "\n";
	}
}

void LevelsState::InitKeyTime()
{
	this->keyTimeMax = 0.3f;
	this->keyTimer.restart();
}

void LevelsState::InitPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player, this->stateData->gfxSettings->resolution);
}

void LevelsState::InitEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures, *this->player);
}

void LevelsState::InitTileMap(const std::string file_name)
{
	this->InitLevel(file_name);

	this->tileMap = new TileMap("level_" + std::to_string(this->player->GetCurrentLevel()) + ".slmp");
}

void LevelsState::InitSystems()
{
	this->textTagSystem = new TextTagSystem("Fonts/font3.ttf");
}

void LevelsState::InitDealer()
{
	this->dealer = new Dealer(350.f, 350.f, 470.f, 370.f);
	this->dealer->SetScale(2.f, 2.f);
}

void LevelsState::InitCoin()
{
	this->countOfCoins = 27;
	this->coin = new Coin(13.f, 130.f);
	this->coin->SetScale(1.25f, 1.25f);
	this->showCountOfCoins.setFont(this->font);
	this->showCountOfCoins.setPosition(55.f, 117.f);
	this->showCountOfCoins.setCharacterSize(45);
	this->showCountOfCoins.setString(": " + std::to_string(this->countOfCoins));
}

void LevelsState::InitTeleport()
{
	this->teleport = new Teleport(static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f, static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f);
}

void LevelsState::InitChest()
{
	this->chest = new Chest(this->stateData);
	this->hideChest = false;
}

void LevelsState::InitEndLevelTimer()
{
	this->showNewWeapon = false;
	this->endLevelText.setFont(this->font);
	this->endLevelText.setCharacterSize(50);
	this->endLevelText.setFillColor(sf::Color::White);
	this->endLevelText.setPosition(static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f - this->endLevelText.getGlobalBounds().width - 50.f,
		static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f);
	this->endLevelText.setString(std::to_string(this->endLevelTimer.getElapsedTime().Zero.asSeconds()));
}

void LevelsState::InitLoading()
{
	this->updateLevel = false;

	this->loadingShape.setSize(sf::Vector2f(static_cast<float>(this->stateData->gfxSettings->resolution.width),
		static_cast<float>(this->stateData->gfxSettings->resolution.height)));
	this->loadingShape.setFillColor(sf::Color(20, 20, 20));
	this->loadingText.setFillColor(sf::Color::White);
	this->loadingText.setFont(this->font);
	this->loadingText.setCharacterSize(24);
	this->loadingText.setPosition(this->stateData->gfxSettings->resolution.width / 2 - 50.f, this->stateData->gfxSettings->resolution.height / 2 - 50.f);
	this->loadingText.setString("Loading...");

	this->loadingBack.setFillColor(sf::Color::Black);
	this->loadingBack.setSize(sf::Vector2f(220.f, 25.f));
	this->loadingBack.setPosition(this->loadingText.getPosition().x - 30.f, this->loadingText.getPosition().y + 35.f);

	this->loadingInner.setFillColor(sf::Color::White);
	this->loadingInner.setSize(sf::Vector2f(this->loadingBack.getSize().x / 2.f, this->loadingBack.getSize().y));
	this->loadingInner.setPosition(this->loadingBack.getPosition());
	this->loadingClock.getElapsedTime().Zero;
}

void LevelsState::InitShop()
{
	this->shop = new Shop(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height,
		this->player->GetCurrentLevel(),
		this->stateData->gfxSettings->resolution
	);

	this->result = 0;
	this->openShop = false;
	this->buySwordsmen = false;
}

void LevelsState::initAimDir()
{
	this->aimDir = new AimDirection();
	this->showAimDir = false;
}

void LevelsState::InitFireShot()
{
	this->fireShot = new FireShot(this->aimDir->getPosition().x, this->aimDir->getPosition().y, this->aimDir->getAngle());
	this->shot = false;
}

void LevelsState::InitSwordsmen()
{
	this->swordsmen = new Swordsmen(50.f, 50.f, this->textures["SWORDSMEN_SHEET"], *this->player);
}

//Constructors / Destructors
LevelsState::LevelsState(StateData* state_data, int currentLevel)
	: State(state_data)
{
	this->InitDeferredRender();
	this->InitView();
	this->InitKeybinds();
	this->InitPlayers();
	this->InitFonts();
	this->InitTextures();
	this->InitPauseMenu();
	this->InitDiedMenu();
	this->InitShaders();
	this->InitKeyTime();
	this->InitPlayerGUI();
	this->InitEnemySystem();
	this->InitTileMap("level.slmp");
	this->InitSystems();
	this->InitDealer();
	this->InitCoin();
	this->InitTeleport();
	this->InitChest();
	this->InitLoading();
	this->InitEndLevelTimer();
	this->InitShop();
	this->initAimDir();
	this->InitFireShot();
	this->InitSwordsmen();
}

LevelsState::~LevelsState()
{
	delete this->pmenu;
	delete this->diedMenu;
	delete this->player;
	delete this->playerGUI;
	delete this->enemySystem;
	delete this->tileMap;
	delete this->textTagSystem;
	delete this->teleport;
	delete this->coin;
	delete this->dealer;
	delete this->shop;

	for (size_t i = 0; i < this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}
}

const bool& LevelsState::GetUpdateLevel() const
{
	return this->updateLevel;
}

const bool LevelsState::GetKeyTime()
{
	if (this->keyTimer.getElapsedTime().asSeconds() >= this->keyTimeMax)
	{
		this->keyTimer.restart();
		return true;
	}

	return false;
}

const bool& LevelsState::GetHideChest() const
{
	return this->hideChest;
}

sf::Vector2f LevelsState::getRotatedCenter(const sf::RectangleShape& rectangle)
{
	sf::Vector2f position = rectangle.getPosition();
	sf::Vector2f size = rectangle.getSize();
	float angle = rectangle.getRotation();

	// Центр прямоугольника в локальной системе координат
	sf::Vector2f center = position + sf::Vector2f(size.x / 2, size.y / 2);

	// Преобразуем угол в радианы
	float radians = angle * 3.14159265f / 180.0f;

	// Вычисляем смещение центра от позиции прямоугольника
	float cosAngle = cos(radians);
	float sinAngle = sin(radians);

	// Рассчитываем новый центр прямоугольника после поворота
	float offsetX = center.x - position.x;
	float offsetY = center.y - position.y;

	// Ротируем смещение
	float rotatedX = cosAngle * offsetX - sinAngle * offsetY;
	float rotatedY = sinAngle * offsetX + cosAngle * offsetY;

	// Возвращаем реальный центр
	return position + sf::Vector2f(rotatedX, rotatedY);
}

void LevelsState::GoToTeleport()
{
	if (this->player->GetGlobalBounds().intersects(this->teleport->GetGlobalBounds()) && this->enemiesIsDead)
	{
		this->loading = true;
		this->loadingClock.getElapsedTime().asSeconds();
	}
}

//Functions
void LevelsState::UpdateView(const float& dt)
{
	this->view.setCenter(
		std::floor(this->player->GetPosition().x + static_cast<float>(this->stateData->gfxSettings->resolution.width / 2) / 10.f),
		std::floor(this->player->GetPosition().y + static_cast<float>(this->stateData->gfxSettings->resolution.height / 2) / 10.f));

	if (this->tileMap->GetMaxSizeF().x >= this->view.getSize().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
		{
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->GetMaxSizeF().x)
		{
			this->view.setCenter(this->tileMap->GetMaxSizeF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}

	if (this->tileMap->GetMaxSizeF().y >= this->view.getSize().y)
	{
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
		{
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
		}
		else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->GetMaxSizeF().y)
		{
			this->view.setCenter(this->view.getCenter().x, this->tileMap->GetMaxSizeF().y - this->view.getSize().y / 2.f);
		}
	}

	this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
}

void LevelsState::UpdateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->GetKeyTime())
	{
		if (!this->paused)
			this->PauseState();
		else
			this->UnpauseState();
	}
}

void LevelsState::UpdatePlayerInput(const float& dt)
{
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->Move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->Move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		this->player->Move(0.f, -1.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player->Move(0.f, 1.f, dt);
	}
}

void LevelsState::UpdatePlayerGUI(const float& dt)
{
	if (this->player->GetNewWeapon())
	{
		delete this->playerGUI;
		this->playerGUI = new PlayerGUI(this->player, this->stateData->gfxSettings->resolution);
	}

	this->playerGUI->Update(dt);
}

void LevelsState::UpdatePauseMenuButtons()
{
	if (this->pmenu->IsButtonPressed("QUIT"))
		this->EndState();

	int recordLevel = this->player->GetCurrentLevel();

	if (this->pmenu->IsButtonPressed("SAVE"))
	{
		std::ofstream record;

		record.open("Level.slmp");

		if (record.is_open())
		{
			record << recordLevel;
			//std::cout << "Record level is " << recordLevel << "\n";
		}

		record.close();
	}
}

void LevelsState::UpdateDiedMenuButtons()
{
	if (this->diedMenu->IsButtonPressed("MENU"))
		this->EndState();
}

void LevelsState::UpdateTileMap(const float& dt)
{
	this->tileMap->UpdateWorldBoundsCollision(this->player, dt);
	this->tileMap->UpdateTileCollision(this->player, dt);
	this->tileMap->UpdateTiles(this->player, dt, *this->enemySystem);
	this->UpdateCountEnemies();
	//this->UpdateLoadingBar();

	if (this->player->GetGlobalBounds().intersects(this->teleport->GetGlobalBounds()) && this->enemiesIsDead)
	{
		delete this->tileMap;
		this->tileMap = new TileMap("level_" + std::to_string(this->player->GetCurrentLevel()) + ".slmp");
		//std::cout << "Current lvl: " << this->player->GetCurrentLevel() << "\n";
		this->tileMap->UpdateWorldBoundsCollision(this->player, dt);
		this->tileMap->UpdateTileCollision(this->player, dt);
		this->tileMap->UpdateTiles(this->player, dt, *this->enemySystem);

		this->UpdateTeleport();
		this->player->SetNewWeapon();
		this->player->GetAttributeComponent()->hp = this->player->GetAttributeComponent()->hpMax;
	}
}

void LevelsState::UpdatePlayer(const float& dt)
{
	this->player->Update(dt, this->mousePosView, this->view);
}

void LevelsState::UpdateCombatAndEnemies(const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->GetWeapon()->GetAttackTimer())
		this->player->SetInitAttack(true);

	unsigned index = 0;
	for (auto* enemy : this->activeEnemies)
	{
		enemy->Update(dt, this->mousePosView, this->view);

		this->tileMap->UpdateWorldBoundsCollision(enemy, dt);

		this->UpdateCombat(enemy, index, dt);

		if (enemy->IsDead())
		{
			this->showCoin = true;
			this->coins.push_back(new Coin(enemy->GetPosition().x, enemy->GetPosition().y));

			for (auto* i : this->coins)
				i->Update(dt);
			//this->coin->SetPosition(enemy->GetPosition().x, enemy->GetPosition().y);
			//this->coin->Update(dt);
			this->player->GainEXP(enemy->GetGainExp());
			this->textTagSystem->AddTextTag(EXPEREINCE_TAG, this->player->GetPosition().x - 40.f, this->player->GetPosition().y - 30.f, static_cast<int>(enemy->GetGainExp()), "+", "EXP");

			this->tileMap->SetNumberDiedEnemies();
			this->enemySystem->RemoveEnemy(index);
			continue;
		}
		else if (enemy->GetDespawnTimerDone())
		{
			this->enemySystem->RemoveEnemy(index);
			continue;
		}

		++index;
	}

	this->player->SetInitAttack(false);
}

void LevelsState::UpdateCombat(Enemy* enemy, const int index, const float& dt)
{
	std::stringstream ss;

	if (this->player->GetInitAttack() && enemy->GetSpriteDistance(*this->player) < this->player->GetWeapon()->GetRange() /*&&
		enemy->GetDamageTimerDone()*/)
	{
		int dmg = static_cast<int>(this->player->GetDamage());

		switch (this->player->GetDamage())
		{
		case 1:
			dmg = 1;
			this->textTagSystem->AddTextTag(TagTypes::DEFAULT_TAG, enemy->GetPosition().x, enemy->GetPosition().y, "-1", "", "HP");
			break;

		case 2:
			dmg = 2;
			this->textTagSystem->AddTextTag(TagTypes::DEFAULT_TAG, enemy->GetPosition().x, enemy->GetPosition().y, "-2", "", "HP");
			break;

		case 3:
			dmg = 6;
			this->textTagSystem->AddTextTag(TagTypes::CRIT_TAG, enemy->GetPosition().x, enemy->GetPosition().y, "CRIT!");
			break;

		case 4:
			dmg = 6;
			this->textTagSystem->AddTextTag(TagTypes::CRIT_TAG, enemy->GetPosition().x, enemy->GetPosition().y, "-6", "", "HP");
			break;

		case 5:
			dmg = 7;
			this->textTagSystem->AddTextTag(TagTypes::CRIT_TAG, enemy->GetPosition().x, enemy->GetPosition().y, "-7!", "", "HP");
			break;

		default:
			this->textTagSystem->AddTextTag(TagTypes::DEFAULT_TAG, enemy->GetPosition().x, enemy->GetPosition().y, "-" + std::to_string(dmg),
				"", "HP");
			break;
		}

		enemy->LoseHP(dmg);
		enemy->ResetDamageTimer();
		enemy->GetGainExp();
	}

	for (size_t i = 0; i < this->player->GetWeapon()->arrows.size(); i++)
	{
		if (this->player->GetWeapon()->arrows[i].shape.getGlobalBounds().intersects(enemy->GetGlobalBounds()))
		{
			this->player->GetWeapon()->arrows.erase(this->player->GetWeapon()->arrows.begin() + i);
			float dmg = static_cast<float>(this->player->GetDamage());

			switch (this->player->GetWeapon()->GetDamage())
			{
			case 7:
				dmg = 1.f;
				this->textTagSystem->AddTextTag(TagTypes::DEFAULT_TAG, enemy->GetPosition().x, enemy->GetPosition().y, "-1", "", "HP");
				break;

			case 8:
				dmg = 2.f;
				this->textTagSystem->AddTextTag(TagTypes::DEFAULT_TAG, enemy->GetPosition().x, enemy->GetPosition().y, "-2", "", "HP");
				break;

			case 9:
				dmg = 0.f;
				this->textTagSystem->AddTextTag(TagTypes::MISS_TAG, enemy->GetPosition().x, enemy->GetPosition().y, "MISS");
				break;

			case 10:
				dmg = 3.f;
				this->textTagSystem->AddTextTag(TagTypes::DEFAULT_TAG, enemy->GetPosition().x, enemy->GetPosition().y, "-3", "", "HP");
				break;

			case 11:
				dmg = 7.f;
				this->textTagSystem->AddTextTag(TagTypes::CRIT_TAG, enemy->GetPosition().x, enemy->GetPosition().y, "-7!", "", "HP");
				break;

			default:
				this->textTagSystem->AddTextTag(TagTypes::DEFAULT_TAG, enemy->GetPosition().x, enemy->GetPosition().y, "-"
					+ std::to_string(dmg), "", "HP");
				break;
			}

			enemy->LoseHP(dmg);
			enemy->ResetDamageTimer();
			enemy->GetGainExp();
		}
	}

	if (enemy->GetGlobalBounds().intersects(this->player->GetGlobalBounds()) && this->player->GetDamageTimer())
	{
		int dmg = enemy->GetAttributeComponent()->damageMax;
		this->player->LoseHP(dmg);
		this->textTagSystem->AddTextTag(TagTypes::NEGATIVE_TAG, player->GetPosition().x - 30.f, player->GetPosition().y, "-"
			+ std::to_string(dmg), "", "HP");
	}

	if (this->player->GetAttributeComponent()->hp == 0)
		this->PlayerDied();

	if (this->swordsmen->GetGlobalBounds().intersects(enemy->GetGlobalBounds()) && this->swordsmen->GetDamageTimer())
		this->swordsmen->GetDamage();
}

void LevelsState::UpdateChest()
{
	if (this->activeEnemies.size() == 0)
	{
		this->hideChest = true;
		this->player->SetEnemiesDead();

		//std::cout << "weapon level: " << this->player->GetWeaponLevel() << std::endl;

		if (this->player->GetRandom() == 0)
		{
			if (!this->newWeaponTexture.loadFromFile("Resources/Sprites/Player/sword_" + std::to_string(this->player->GetWeaponLevel()) + ".png")) exit(15);
		}
		else if (this->player->GetRandom() == 1)
		{
			if (!this->newWeaponTexture.loadFromFile("Resources/Sprites/Player/bow_" + std::to_string(this->player->GetWeaponLevel()) + ".png")) exit(15);
		}

		this->newWeapon.setTexture(this->newWeaponTexture);
		this->newWeapon.setPosition(this->chest->GetChest().getPosition());
		this->newWeaponText.setFillColor(sf::Color::White);
		this->newWeaponText.setFont(this->font);
		this->newWeaponText.setCharacterSize(14);
		this->newWeaponText.setPosition(this->newWeapon.getPosition().x + 5.f, this->newWeapon.getPosition().y - 10.f);
		this->newWeaponText.setString("Press E to pick up a new weapon");
	}
}

void LevelsState::UpdateEndLevelTimer()
{
	this->endLevelText.setString(std::to_string(this->endLevelTimer.getElapsedTime().asSeconds()));
}

void LevelsState::UpdateLoading()
{
	this->loadingClock.getElapsedTime().asSeconds();
}

void LevelsState::UpdateTeleport()
{
	this->teleport->SetPosition(this->player->GetPosition().x + 100.f, this->player->GetPosition().y);
}

void LevelsState::UpdateLoadingBar()
{
	this->loadingInner.setSize(sf::Vector2f(this->loadingClock.getElapsedTime().asSeconds() * 20, 25.f));

	if (this->loadingInner.getSize().x / 20.f >= 11.f)
	{
		this->loading = false;

		this->player->IncreaseNewLevel(1);

		while (this->player->GetCurrentLevel() < this->player->GetNewLevel())
			this->player->IncreaseCurrentLevel(1);


		if (this->player->GetCurrentLevel() % 5 == 0)
		{
			std::cout << "weapon level: " << this->player->GetWeaponLevel() << "\n";
			this->player->IncreaseWeaponLevel(1);
		}

		//this->InitLevel("level.slmp");
	}
}

void LevelsState::UpdateCountEnemies()
{
	if (this->activeEnemies.size() == 0)
		this->enemiesIsDead = true;
	else
		this->enemiesIsDead = false;
}

void LevelsState::UpdateRecordLevelInFile()
{
	int recordLevel = this->player->GetCurrentLevel();

	if (this->died)
	{
		std::ofstream record;

		record.open("Level.slmp");

		if (record.is_open())
		{
			record << recordLevel;
			//std::cout << "Record level is " << recordLevel << "\n";
		}

		record.close();

		//this->player->SetCurrentLevel(recordLevel);
	}
}

void LevelsState::PickUpCoin()
{
	this->showCountOfCoins.setString(": " + std::to_string(this->countOfCoins));

	for (size_t i = 0; i < this->coins.size(); i++)
	{
		if (this->player->GetGlobalBounds().intersects(this->coins[i]->GetGlobalBounds()))
		{
			this->coins.erase(this->coins.begin() + i);
			this->countOfCoins++;
		}
	}
}

void LevelsState::UpdateShop()
{
	if (this->player->GetPosition().x - this->dealer->GetPosition().x > -50.f &&
		this->player->GetPosition().x - this->dealer->GetPosition().x < 160.f &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::F) &&
		this->GetKeyTime())
	{
		if (!this->openShop)
			this->openShop = true;
		else
			this->openShop = false;
	}
}

void LevelsState::updateAimDir()
{
	this->aimDir->update(this->mousePosView, this->player);
}

void LevelsState::Update(sf::Music* music, const float& dt)
{
	this->UpdateMousePositions(&this->view);
	this->UpdateInput(dt);

	//std::cout << "currentLevel: " << this->player->GetCurrentLevel() << "\n";

	//for (auto* enemy : this->activeEnemies)
	//{
	//	std::cout << "Count: " << enemy->GetEnemySpawnerTile().GetEnemyAmount() << "\n";
	//}

	if (this->died)
		this->UpdateRecordLevelInFile();	

	if (!this->paused && !this->died && !this->loading) //Unpaused update
	{
		this->UpdateView(dt);

		this->UpdatePlayerInput(dt);

		this->UpdateTileMap(dt);

		//this->UpdateChest();

		this->UpdatePlayer(dt);

		//if (!this->player->GetUpdateBow())
		//{
			this->player->GetWeapon()->Update(mousePosView,
				sf::Vector2f(this->player->GetCenter().x, this->player->GetCenter().y + 10.f),
				view);
		//}

		this->UpdateChest();

		this->UpdatePlayerGUI(dt);

		this->UpdateCombatAndEnemies(dt);
		this->UpdateCountEnemies();

		this->teleport->Update(dt);
		this->updateAimDir();

		
		
		for (auto* i : this->coins)
			i->Update(dt);

		//Update systems
		this->textTagSystem->Update(dt);
		this->loadingClock.restart();
		this->GoToTeleport();
		this->PickUpCoin();
		this->dealer->Update(dt);
		this->UpdateShop();

		for (auto* i : this->shop->GetArrayCards())
		{
			if (i->GetType() == 2 && this->GetKeyTime())
			{
				if (this->countOfCoins >= i->GetPrice())
				{
					this->countOfCoins -= i->GetPrice();

					if (i->GetClick() && i->GetId() == 1)
					{
						this->player->UpdateSword();
						this->player->SetUpdateBowTrue();
					}
					else if (i->GetClick() && i->GetId() == 2)
					{
						//this->player->UpdateBow();
						this->player->UpdateBow();
						this->player->SetUpdateBowTrue();
					}
					else if (i->GetClick() && i->GetId() == 3)
					{
						this->player->SetModifier(TypesOfModifeirs::COMBUSTION);
						this->swordModify == SwordModifiers::FLAME;

						//std::cout << "Type: " << this->player->GetWeapon()->GetModifiers() << "\n";

						this->player->SetUpdateBowTrue();
					}
					else if (i->GetClick() && i->GetId() == 4)
					{
						this->player->SetModifier(TypesOfModifeirs::FREEZING);
						this->swordModify == SwordModifiers::ICE;

						//std::cout << "Type: " << this->player->GetWeapon()->GetModifiers() << "\n";

						this->player->SetUpdateBowTrue();
					}
					else if (i->GetClick() && i->GetId() == 5)
					{
						this->buySwordsmen = true;
					}
				}
			}
		}

		if (this->player->GetTypeOfModify() == ModifyTypes::COMB)
		{
			for (auto* enemy : this->activeEnemies)
			{
				enemy->SetModify(ModifyTypes::COMB);
			}
		}

		if (this->player->GetTypeOfModify() == ModifyTypes::FREEZ)
		{
			for (auto* enemy : this->activeEnemies)
			{
				enemy->SetModify(ModifyTypes::FREEZ);
			}
		}

		//Swordsmen* swordsmen = new Swordsmen(0.f, 0.f, this->newWeaponTexture, *this->player);

		if (this->buySwordsmen)
		{
			std::thread swThread([&]() {swordsmen->Update(dt, mousePosView, view); });
			swThread.join();
			//this->swordsmenThread = [this, swordsmen, dt]() {swordsmen->Update(dt, mousePosView, view); };
			
			this->swordsmen->Update(dt, this->mousePosView, this->view);
		}

		if (this->player->GetUpdateBow())
		{
			this->player->GetWeapon()->Update(
				this->mousePosView,
				sf::Vector2f(this->player->GetCenter().x, this->player->GetCenter().y + 10.f),
				this->view
			);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		this->showAimDir = true;

	else if (this->paused)//Paused update
	{
		this->pmenu->Update(this->mousePosWindow);
		this->UpdatePauseMenuButtons();
	}
	else if (this->died)
	{
		this->diedMenu->Update(this->mousePosWindow);
		this->UpdateDiedMenuButtons();
	}
	else if (this->loading)
	{
		this->UpdateLoading();
		this->UpdateLoadingBar();
		//std::cout << "level: " << this->player->GetCurrentLevel()<<"\n";
		//this->InitLevel("Level.slmp");
	}

	if (this->openShop)
		this->shop->Update(static_cast<sf::Vector2f>(this->mousePosWindow));

	//std::cout << this->player->GetPosition().x - this->dealer->GetPosition().x << std::endl;

	if (this->player->GetPosition().x - this->dealer->GetPosition().x > -50.f &&
		this->player->GetPosition().x - this->dealer->GetPosition().x < 160.f)
		this->dealer->SetShopTrue();
	else
		this->dealer->SetShopFalse();

	if (this->player->GetNewWeapon())
	{
		this->UpdateEndLevelTimer();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		this->shot = true;
	}

	if (this->activeEnemies.size() != 0)
	{
		for (auto* enemy : this->activeEnemies)
			this->swordsmen->CheckIsEnemiesInTileMap(*enemy);
	}

	if (this->player->GetCurrentLevel() % 5 == 0)
	{
		switch (this->player->GetCurrentLevel())
		{
			int level;
		case 5:
			level = 2;
			for (auto& enemy : this->activeEnemies)
			{
				enemy->CreateAttributeComponent(level);
			}
			break;

		case 10:
			level = 3;
			for (auto& enemy : this->activeEnemies)
				enemy->CreateAttributeComponent(level);
			break;

		case 15:
			level = 4;
			for (auto& enemy : this->activeEnemies)
				enemy->CreateAttributeComponent(level);
			break;

		case 20:
			level = 5;
			for (auto& enemy : this->activeEnemies)
				enemy->CreateAttributeComponent(level);
			break;
		}
	}

	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->GetKeyTime())
		this->fireShots.push_back(new FireShot(this->player->GetPosition().x, this->player->GetPosition().y));*/

		if (this->showAimDir && sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->GetKeyTime())
		{
			sf::Vector2f center = this->aimDir->getPosition();
			/*sf::Vector2f center;
			sf::Vector2f firePosition = this->aimDir->getPosition();
			if (this->aimDir->getAngle() < 0.f && this->aimDir->getAngle() > -90.f)
				center = firePosition - sf::Vector2f(this->aimDir->getSize().x / 3.f, 0.f);
			else 
				center = firePosition + sf::Vector2f(this->aimDir->getSize().x / 3.f, 0.f);

			if (this->aimDir->getAngle() > 0.f && this->aimDir->getAngle() < 90.f)
				center = firePosition - sf::Vector2f(0.f, this->aimDir->getSize().x / 3.f);
			else
				center = firePosition + sf::Vector2f(0.f, this->aimDir->getSize().x / 3.f);*/

			//firePosition += sf::Vector2f(std::cos(this->aimDir->getAngle()), std::sin(this->aimDir->getAngle()));

			//firePosition.y -= 45.f;
			//firePosition.x -= 20.f;
			this->shot = true;
			this->fireShots.push_back(new FireShot(center.x, center.y, this->aimDir->getAngle()));
		}

	for (auto& shot : this->fireShots)
	{
		shot->Update(dt);
	}
		/*this->fireShot->Update(dt);*/
}

void LevelsState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);

	this->tileMap->Render(
		this->renderTexture,
		this->viewGridPosition,
		&this->coreShader,
		this->player->GetCenter(),
		false
	);

	for (auto* enemy : this->activeEnemies)
	{
		enemy->Render(this->renderTexture, &this->coreShader, this->player->GetCenter());
	}

	if (this->buySwordsmen)
		this->swordsmen->Render(this->renderTexture, &this->coreShader, this->swordsmen->GetCenter());

	this->player->Render(this->renderTexture, &this->coreShader, this->player->GetCenter());

	this->tileMap->DefferedRender(this->renderTexture, &this->coreShader, this->player->GetCenter());

	this->textTagSystem->Render(this->renderTexture);

	if (this->showCoin)
	{
		for (auto* i : this->coins)
			i->Render(this->renderTexture, &this->coreShader, this->player->GetCenter());
	}

	if (this->enemiesIsDead)
		this->teleport->Render(this->renderTexture, &this->coreShader, this->teleport->GetCenter());

	this->dealer->Render(this->renderTexture, &this->coreShader, this->dealer->GetCenter());
	
	if (this->shot)
		this->fireShot->Render(this->renderTexture, &this->coreShader, this->fireShot->GetCenter());

	if (this->showAimDir)
		this->aimDir->render(this->renderTexture);

	if (this->player->GetCurrentLevel() % 5 == 0)
	{
		if (!this->hideChest)
			this->chest->Render(this->renderTexture);
	}

	for (auto* shot : this->fireShots)
	{
		shot->Render(this->renderTexture, &this->coreShader, this->player->GetCenter());
	}

	if (this->showNewWeapon)
	{
		if (!this->player->GetNewWeapon())
		{
			this->renderTexture.draw(this->newWeapon);
			if (this->player->GetPosition().x - this->newWeapon.getPosition().x <= 20.f || this->newWeapon.getPosition().x - this->player->GetPosition().x <= 20.f)
				this->renderTexture.draw(this->newWeaponText);
		}
	}

	//Render GUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->Render(this->renderTexture);
	this->coin->Render(this->renderTexture, &this->coreShader, this->coin->GetCenter());
	this->renderTexture.draw(this->showCountOfCoins);


	if (this->openShop)
		this->shop->Render(this->renderTexture, &this->coreShader, this->shop->GetCenter());

	if (this->paused) //Pause menu Render
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->Render(this->renderTexture);
	}

	if (this->died)
		this->diedMenu->Render(this->renderTexture);

	if (this->loading)
	{
		this->renderTexture.draw(this->loadingShape);
		this->renderTexture.draw(this->loadingBack);
		this->renderTexture.draw(this->loadingInner);
		this->renderTexture.draw(this->loadingText);
	}

	this->renderTexture.display();
	target->draw(this->renderSprite);
}