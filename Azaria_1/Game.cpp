#include "stdafx.h"
#include "Game.h"

//Static functions

//Initializer functions
void Game::InitVariables()
{
	this->window = NULL;
	this->dt = 0.f;
	this->gridSize = 64.f;
}

void Game::InitGraphicsSettings()
{
	this->gfxSettings.LoadFromFile("Config/graphics.txt");
	//this->stateData.gfxSettings->resolution.width
}

void Game::InitWindow()
{
	/*Creates a SFML window.*/

	if (this->gfxSettings.fullscreen)
		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution,
			this->gfxSettings.title,
			sf::Style::Fullscreen,
			this->gfxSettings.contextSettings);
	else
		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution,
			this->gfxSettings.title,
			sf::Style::Titlebar | sf::Style::Close,
			this->gfxSettings.contextSettings);

	this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::InitKeys()
{
	std::ifstream ifs("Config/keybinds.txt");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}

	ifs.close();

	//DEBUG REMOVE LATER!
	//for (auto i : this->supportedKeys)
	//{
	//	std::cout << i.first << " " << i.second << "\n";
	//}
}

void Game::InitStateData()
{
	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
}

void Game::InitStates()
{
	this->states.push(new MainMenuState(&this->stateData));
}

//Constructors/Destructors
Game::Game()
{
	this->InitVariables();
	this->InitGraphicsSettings();
	this->InitWindow();
	this->InitKeys();
	this->InitStateData();
	this->InitStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

//Functions
void Game::EndApplication()
{
	std::cout << "Ending Application!" << "\n";
}

void Game::UpdateDt()
{
	/*Updates the dt variable with the time it takes to update and render one frame.*/

	this->dt = this->dtClock.restart().asSeconds();
}

void Game::UpdateSFMLEvents()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::Update()
{
	this->UpdateSFMLEvents();

	if (!this->states.empty())
	{
		if (this->window->hasFocus())
		{
			this->states.top()->Update(&this->music, this->dt);

			if (this->states.top()->GetQuit())
			{
				this->states.top()->EndState();
				delete this->states.top();
				this->states.pop();
			}
		}
	}

	//Application end
	else
	{
		this->EndApplication();
		this->window->close();
	}
}

void Game::Render()
{
	this->window->clear();

	//Render items
	if (!this->states.empty())
		this->states.top()->Render();

	this->window->display();
}

void Game::Run()
{
	while (this->window->isOpen())
	{
		this->UpdateDt();
		this->Update();
		this->Render();
	}
}