#include "stdafx.h"
#include "ArcadaState.h"

void ArcadaState::InitDeferredRender()
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
void ArcadaState::InitView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width) / 1.3,
			static_cast<float>(this->stateData->gfxSettings->resolution.height) / 1.3
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
			static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
		)
	);
}

void ArcadaState::InitKeybinds()
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

void ArcadaState::InitFonts()
{
	if (!this->font.loadFromFile("Fonts/font3.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void ArcadaState::InitTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Sprites/Player/player.png"))
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

	//if (!this->textures["MINOTAUR_SHEET"].loadFromFile("Resources/Sprites/Enemy/minotaur.png"))
	//{
	//	throw "ERROR::GAME_STATE::COULD_NOT_LOAD_BIRD1_TEXTURE";
	//}
}

void ArcadaState::InitGameTimer()
{
	this->gameTimerText.setFont(this->font);
	this->gameTimerText.setCharacterSize(50);
	this->gameTimerText.setFillColor(sf::Color::White);
	this->gameTimerText.setPosition(this->stateData->gfxSettings->resolution.width / 2.f - this->gameTimerText.getGlobalBounds().width - 50.f, 10.f);
	this->gameTimerText.setString(std::to_string(this->gameTimer.asSeconds()));

	//std::cout << this->gameTimer.asSeconds();
}

void ArcadaState::InitPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->AddButton("QUIT", GUI::p2pY(74.f, vm), GUI::p2pX(13.f, vm), GUI::p2pY(6.f, vm), GUI::calcCharSize(vm), "Quit");
}

void ArcadaState::InitDiedMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->diedMenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font, "YOU DEAD!", sf::Color::Red, true);

	this->diedMenu->AddButton("MENU", GUI::p2pY(50.f, vm), GUI::p2pX(13.f, vm), GUI::p2pY(6.f, vm), GUI::calcCharSize(vm), "Menu");

}

void ArcadaState::InitShaders()
{
	if (!this->coreShader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER." << "\n";
	}
}

void ArcadaState::InitKeyTime()
{
	this->keyTimeMax = 0.3f;
	this->keyTimer.restart();
}

void ArcadaState::InitDebugText()
{
	this->debugText.setFont(this->font);
	this->debugText.setFillColor(sf::Color::White);
	this->debugText.setCharacterSize(16);
	this->debugText.setPosition(15.f, this->window->getSize().y / 2.f);
}

void ArcadaState::InitPlayers()
{
	this->player = new Player(220, 220, this->textures["PLAYER_SHEET"], this->stateData->gfxSettings->resolution);
}

void ArcadaState::InitPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player, this->stateData->gfxSettings->resolution);
}

void ArcadaState::InitEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures, *this->player);
}

void ArcadaState::InitTileMap()
{
	this->tileMap = new TileMap("arcada.slmp");
}

void ArcadaState::InitSystems()
{
	this->textTagSystem = new TextTagSystem("Fonts/font3.ttf");
}

//Constructors / Destructors
ArcadaState::ArcadaState(StateData* state_data)
	: State(state_data)
{
	this->InitDeferredRender();
	this->InitView();
	this->InitKeybinds();
	this->InitFonts();
	this->InitTextures();
	this->InitPauseMenu();
	this->InitDiedMenu();
	this->InitShaders();
	this->InitKeyTime();
	this->InitDebugText();
	this->InitGameTimer();
	this->InitPlayers();
	this->InitPlayerGUI();
	this->InitEnemySystem();
	this->InitTileMap();
	this->InitSystems();
}

ArcadaState::~ArcadaState()
{
	delete this->pmenu;
	delete this->diedMenu;
	delete this->player;
	delete this->playerGUI;
	delete this->enemySystem;
	delete this->tileMap;
	delete this->textTagSystem;

	for (size_t i = 0; i < this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}
}

const bool ArcadaState::GetKeyTime()
{
	if (this->keyTimer.getElapsedTime().asSeconds() >= this->keyTimeMax)
	{
		this->keyTimer.restart();
		return true;
	}

	return false;
}

//Functions
void ArcadaState::UpdateView(const float& dt)
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

void ArcadaState::UpdateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->GetKeyTime())
	{
		if (!this->paused)
			this->PauseState();
		else
			this->UnpauseState();
	}
}

void ArcadaState::UpdatePlayerInput(const float& dt)
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

void ArcadaState::UpdatePlayerGUI(const float& dt)
{
	this->playerGUI->Update(dt);

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TOGGLE_PLAYER_TAB_CHARACTER"))) && this->GetKeytime())
	//{
	//	this->playerGUI->ToggleCharacterTab();
	//}
}

void ArcadaState::UpdatePauseMenuButtons()
{
	if (this->pmenu->IsButtonPressed("QUIT"))
		this->EndState();
}

void ArcadaState::UpdateDiedMenuButtons()
{
	if (this->diedMenu->IsButtonPressed("MENU"))
		this->EndState();
}

void ArcadaState::UpdateTileMap(const float& dt)
{
	this->tileMap->UpdateWorldBoundsCollision(this->player, dt);
	this->tileMap->UpdateTileCollision(this->player, dt);
	this->tileMap->UpdateTiles(this->player, dt, *this->enemySystem);
}

void ArcadaState::UpdatePlayer(const float& dt)
{
	this->player->Update(dt, this->mousePosView, this->view);
}

void ArcadaState::UpdateGameTimer()
{

	this->gameTimerText.setString(std::to_string(this->gameClock.getElapsedTime().asSeconds()));
}

void ArcadaState::UpdateCombatAndEnemies(const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->GetWeapon()->GetAttackTimer())
		this->player->SetInitAttack(true);

	unsigned index = 0;
	for (auto* enemy : this->activeEnemies)
	{
		enemy->Update(dt, this->mousePosView, this->view);

		this->tileMap->UpdateWorldBoundsCollision(enemy, dt);
		this->tileMap->UpdateTileCollision(enemy, dt);

		this->UpdateCombat(enemy, index, dt);

		if (enemy->IsDead())
		{
			this->player->GainEXP(enemy->GetGainExp());
			this->textTagSystem->AddTextTag(EXPEREINCE_TAG, this->player->GetPosition().x - 40.f, this->player->GetPosition().y - 30.f, static_cast<int>(enemy->GetGainExp()), "+", "EXP");

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

void ArcadaState::UpdateCombat(Enemy* enemy, const int index, const float& dt)
{
	std::stringstream ss;

	if (this->player->GetInitAttack() && enemy->GetSpriteDistance(*this->player) < this->player->GetWeapon()->GetRange() &&
		enemy->GetDamageTimerDone())
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
			dmg = 0;
			this->textTagSystem->AddTextTag(TagTypes::MISS_TAG, enemy->GetPosition().x, enemy->GetPosition().y, "MISS");
			break;

		case 4:
			dmg = 3;
			this->textTagSystem->AddTextTag(TagTypes::DEFAULT_TAG, enemy->GetPosition().x, enemy->GetPosition().y, "-3", "", "HP");
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
			int dmg = static_cast<int>(this->player->GetDamage());

			switch (this->player->GetWeapon()->GetDamage())
			{
			case 7:
				dmg = 1;
				this->textTagSystem->AddTextTag(TagTypes::DEFAULT_TAG, enemy->GetPosition().x, enemy->GetPosition().y, "-1", "", "HP");
				break;

			case 8:
				dmg = 2;
				this->textTagSystem->AddTextTag(TagTypes::DEFAULT_TAG, enemy->GetPosition().x, enemy->GetPosition().y, "-2", "", "HP");
				break;

			case 9:
				dmg = 0;
				this->textTagSystem->AddTextTag(TagTypes::MISS_TAG, enemy->GetPosition().x, enemy->GetPosition().y, "MISS");
				break;

			case 10:
				dmg = 3;
				this->textTagSystem->AddTextTag(TagTypes::DEFAULT_TAG, enemy->GetPosition().x, enemy->GetPosition().y, "-3", "", "HP");
				break;

			case 11:
				dmg = 7;
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
}

void ArcadaState::UpdateDebugText(const float& dt)
{
	std::stringstream ss;

	ss << "Mouse Pos View: " << this->mousePosView.x << " " << this->mousePosView.y << "\n"
		<< "Active Enemies: " << this->activeEnemies.size() << "\n";

	this->debugText.setString(ss.str());
}

void ArcadaState::RecordBestTime()
{
	std::ofstream in_file;

	in_file.open("score.slmp");

	if (in_file.is_open())
	{
		in_file << this->gameClock.getElapsedTime().asSeconds();
	}

	in_file.close();
}

void ArcadaState::Update(sf::Music* music, const float& dt)
{
	this->UpdateMousePositions(&this->view);
	//this->UpdateKeyTime(dt);
	this->UpdateInput(dt);

	this->UpdateDebugText(dt);

	if (!this->paused && !this->died) //Unpaused update
	{
		this->UpdateView(dt);

		this->UpdatePlayerInput(dt);

		this->UpdateTileMap(dt);

		this->UpdatePlayer(dt);

		this->UpdatePlayerGUI(dt);

		this->UpdateCombatAndEnemies(dt);
		this->UpdateGameTimer();

		//Update systems
		this->textTagSystem->Update(dt);

		this->RecordBestTime();
	}
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
}

void ArcadaState::Render(sf::RenderTarget* target)
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

	this->player->Render(this->renderTexture, &this->coreShader, this->player->GetCenter());

	this->tileMap->DefferedRender(this->renderTexture, &this->coreShader, this->player->GetCenter());

	this->textTagSystem->Render(this->renderTexture);

	//Render GUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->Render(this->renderTexture);

	if (this->paused) //Pause menu Render
	{
		//this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->Render(this->renderTexture);
	}

	if (this->died)
		this->diedMenu->Render(this->renderTexture);

	//Debug Text
	this->renderTexture.draw(this->debugText);

	//FINAL RENDER
	this->renderTexture.draw(this->gameTimerText);
	this->renderTexture.display();
	//this->RenderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}