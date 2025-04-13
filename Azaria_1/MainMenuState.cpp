#include "stdafx.h"
#include "MainMenuState.h"

//Initializer functions
void MainMenuState::InitVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
	this->isSet = false;
	this->loadLevel = 3;
}

void MainMenuState::InitLevel(const std::string file_name)
{
	std::ifstream in_file;

	in_file.open(file_name);

	if (in_file.is_open())
	{
		in_file >> this->loadLevel;
		//std::cout << "Menu level: " << this->loadLevel << "\n";
	}

	in_file.close();
}

void MainMenuState::InitMusic()
{
	if (!this->music.openFromFile("Music/menu_music.wav")) exit(8);
	this->music.setVolume(30.f);
	this->music.play();
}

void MainMenuState::InitFonts()
{
	if (!this->font.loadFromFile("Fonts/font3.ttf")) exit(3);
}

void MainMenuState::InitKeybinds()
{
	std::ifstream ifs("Config/menustate_key.txt");

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

void MainMenuState::InitBestScore()
{
	std::ifstream out_file;

	out_file.open("score.slmp");

	if (out_file.is_open())
	{
		out_file >> score;
	}

	this->bestScore.setFont(this->font);
	this->bestScore.setCharacterSize(50);
	this->bestScore.setFillColor(sf::Color(212, 153, 2, 255));
	this->bestScore.setPosition(this->stateData->gfxSettings->resolution.width / 2 - 350, 50.f);
	this->bestScore.setString("Best score in arcada: " + std::to_string(score));
}

void MainMenuState::InitGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->specialFont.loadFromFile("Fonts/font.ttf");

	this->background.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));

	if (!this->bgTex.loadFromFile("Resources/Images/Backgrounds/menubg.jpg")) exit(3);

	this->background.setTexture(&this->bgTex);

	this->buttons["COMPANY_STATE"] = new GUI::Button(
		GUI::p2pX(14.8f, vm), GUI::p2pY(45.7f, vm), GUI::p2pX(14.8f, vm), GUI::p2pY(6.1f, vm),
		&this->font, "Company", GUI::calcCharSize(vm),
		sf::Color(212, 153, 2, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50), // 150 30 241 - purple
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["ARCADA_STATE"] = new GUI::Button(
		GUI::p2pX(14.8f, vm), GUI::p2pY(55.2f, vm), GUI::p2pX(14.8f, vm), GUI::p2pY(6.1f, vm),
		&this->font, "Arcada", GUI::calcCharSize(vm),
		sf::Color(212, 153, 2, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50), // 150 30 241 - purple
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["SETTINGS"] = new GUI::Button(
		GUI::p2pX(14.8f, vm), GUI::p2pY(64.7f, vm), GUI::p2pX(14.8f, vm), GUI::p2pY(6.1f, vm),
		&this->font, "Settings", GUI::calcCharSize(vm),
		sf::Color(212, 153, 21, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50), // 70, 70, 70, 200 - base
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 5), sf::Color(20, 20, 20, 0)
	);

	this->buttons["EDITOR"] = new GUI::Button(
		GUI::p2pX(14.8f, vm), GUI::p2pY(74.2f, vm), GUI::p2pX(14.8f, vm), GUI::p2pY(6.1f, vm),
		&this->font, "Editor", GUI::calcCharSize(vm),
		sf::Color(212, 153, 2, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50), // 47 162 7 - green
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 5), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new GUI::Button(
		GUI::p2pX(14.8f, vm), GUI::p2pY(83.7f, vm), GUI::p2pX(14.8f, vm), GUI::p2pY(6.1f, vm),
		&this->font, "Quit", GUI::calcCharSize(vm),
		sf::Color(212, 153, 2, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50), // 212 153 2 - orange
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["APPLY"] = new GUI::Button(
		GUI::p2pX(42.7f, vm), GUI::p2pY(53.4f, vm), GUI::p2pX(14.8f, vm), GUI::p2pY(6.1f, vm),
		&this->font, "Apply", GUI::calcCharSize(vm),
		sf::Color(212, 153, 2, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50), // 212 153 2 - orange
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font, "Please set your resolution", sf::Color::White, true);

	std::vector<std::string> modesStr;

	for (auto& i : this->modes)
		modesStr.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));

	this->resolutionList["RESOLUTION"] = new GUI::DropDownList(GUI::p2pX(44.f, vm), GUI::p2pY(50.4f, vm), GUI::p2pX(11.9f, vm),
		GUI::p2pY(4.7f, vm), specialFont, modesStr.data(), static_cast<unsigned>(modesStr.size()));
}

void MainMenuState::ResetGui()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
		delete it->second;

	this->buttons.clear();
	this->InitGui();
}

MainMenuState::MainMenuState(StateData* stateData)
	: State(stateData)
{
	this->InitVariables();
	this->InitLevel("Level.slmp");
	this->InitMusic();

	this->player = new Player();
	this->settingsState = new SettingsState(&this->music, stateData);

	this->InitFonts();
	this->InitKeybinds();
	this->InitBestScore();
	this->InitGui();
	this->ResetGui();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


void MainMenuState::UpdateInput(const float& dt)
{

}

void MainMenuState::UpdateButtons(const float& dt, std::string file_name)
{
	/*Updates all the buttons in the state and handles their functionlaity.*/

	for (auto& it : this->buttons)
	{
		it.second->Update(this->mousePosWindow);
	}

	//for (auto& it : this->resolutionList)
	//{
	//	it.second->Update(this->mousePosWindow, dt);
	//}

	//New game
	if (this->isSet)
	{
		if (this->buttons["COMPANY_STATE"]->IsPressed())
		{
			this->states->push(new LevelsState(this->stateData, this->loadLevel));

			if (this->player->GetNewWeapon())
			{
				this->states->top()->EndState();
				delete this->states->top();
				this->states->push(new LevelsState(this->stateData, this->loadLevel + 1));
			}

			this->music.stop();
		}

		if (this->buttons["ARCADA_STATE"]->IsPressed()/* || this->newLevel*/)
		{
			this->states->push(new ArcadaState(this->stateData));
			this->music.stop();
		}

		if (this->buttons["SETTINGS"]->IsPressed())
		{
			this->states->push(new SettingsState(&this->music, this->stateData));
			//this->ResetGui();
		}

		if (this->buttons["EDITOR"]->IsPressed())
		{
			this->states->push(new EditorState(this->stateData));
			this->music.stop();
		}
	}

	if (this->buttons["APPLY"]->IsPressed())
	{
		this->isSet = true;
		this->stateData->gfxSettings->resolution = this->modes[this->resolutionList["RESOLUTION"]->GetActiveElementId()];

		this->ResetGui();

		std::ofstream out_file;

		out_file.open(file_name);

		if (out_file.is_open())
		{
			out_file << "Azaria" << "\n"
				<< this->stateData->gfxSettings->resolution.width << " " << this->stateData->gfxSettings->resolution.height << "\n"
				<< 1 << "\n"
				<< 120 << "\n"
				<< 0 << "\n"
				<< 0 << "\n"
				<< 1 << "\n";
		}
		else
		{
			std::cout << "ERROR::RESOLUTION/AVE TO FILE::FILENAME: " << file_name << "\n";
		}
	}


	for (auto& it : this->resolutionList)
	{
		it.second->Update(this->mousePosWindow, dt);
	}



	//Quit the game
	if (this->buttons["EXIT_STATE"]->IsPressed())
	{
		this->EndState();
	}

	//this->ResetGui();
}

void MainMenuState::UpdateMusic()
{
	if (this->music.getStatus() == this->music.Stopped)
		this->music.play();

	//if (this->buttons["INCREASE_VOLUME"]->IsPressed())
	//	this->settingsState->UpdateVolume(&this->music, 10.f);
	//if (this->buttons["DECREASE_VOLUME"]->IsPressed())
	//	this->settingsState->UpdateVolume(&this->music, -10.f);

	//if (this->buttons["INCREASE_VOLUME"]->IsPressed())
	//	this->music.setVolume(this->music.getVolume() + 1.f);
	//else if (this->buttons["DECREASE_VOLUME"]->IsPressed())
	//	this->music.setVolume(this->music.getVolume() - 1.f);

	//if (this->music.getVolume() > 100)
	//	this->music.setVolume(100);
}

void MainMenuState::Update(sf::Music* music, const float& dt)
{
	this->UpdateMousePositions();
	this->UpdateInput(dt);

	this->InitBestScore();

	this->UpdateMusic();
	this->UpdateButtons(dt, "Config/graphics.txt");

	//if (this->buttons["INCREASE_VOLUME"]->IsPressed())
	//	this->settingsState->UpdateVolume(music, 10.f);
	//else if (this->buttons["DECREASE_VOLUME"]->IsPressed())
	//	this->settingsState->UpdateVolume(music, -10.f);
}

void MainMenuState::RenderButtons(sf::RenderTarget& target)
{
	this->buttons["COMPANY_STATE"]->Render(target);
	this->buttons["ARCADA_STATE"]->Render(target);
	this->buttons["SETTINGS"]->Render(target);
	this->buttons["EDITOR"]->Render(target);
	this->buttons["EXIT_STATE"]->Render(target);
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	//target->draw(this->btnBackground);

	this->RenderButtons(*target);

	target->draw(this->bestScore);

	if (!this->isSet)
	{
		this->pmenu->Render(*target);
		for (auto& it : this->resolutionList)
			it.second->Render(*target);
		this->buttons["APPLY"]->Render(*target);
	}

	//REMOVE LATER!!!
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}
