#include"stdafx.h"
#include "State.h"

// Constructor/Destructor
State::State(StateData* stateData, sf::Music* music)
{
	this->stateData = stateData;
	this->window = stateData->window;
	this->supportedKeys = stateData->supportedKeys;
	this->states = stateData->states;
	this->quit = false;
	this->showed = false;
	this->paused = false;
	this->isOpen = false;
	this->newLevel = false;
	this->loading = false;
	this->enemiesIsDead = false;
	this->showCoin = false;
	this->keytime = 0.f;
	this->keytimeMax = 10.f;
	this->gridSize = stateData->gridSize;
	this->currentLevel = 1;

	std::ifstream in_file;

	in_file.open("level.slmp");

	if (in_file.is_open())
	{
		in_file >> this->currentLevel;

		//std::cout << "State call currentLevel: " << this->currentLevel << std::endl;
	}

	in_file.close();
}

State::~State()
{
}

// Functions
const bool& State::GetQuit() const
{
	return this->quit;
}

const bool State::GetKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

void State::EndState()
{
	this->quit = true;
}

void State::ShowedState()
{
	this->showed = true;
}

void State::UnshowedState()
{
	this->showed = false;
}

void State::PauseState()
{
	this->paused = true;
}

void State::UnpauseState()
{
	this->paused = false;
}

void State::PlayerDied()
{
	this->died = true;
}

void State::UpdateLevel()
{
	this->currentLevel += 1;
}

void State::IsOpen()
{
	this->isOpen = true;
}

void State::Close()
{
	this->isOpen = false;
}

void State::UpdateMousePositions(sf::View* view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	if (view)
		this->window->setView(*view);

	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = sf::Vector2i(
		static_cast<int>(this->mousePosView.x) / static_cast<int>(this->gridSize),
		static_cast<int>(this->mousePosView.y) / static_cast<int>(this->gridSize));

	this->window->setView(this->window->getDefaultView());
}

void State::Updatekeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 100.f * dt;
}
