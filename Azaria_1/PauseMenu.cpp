#include"stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::VideoMode& vm, sf::Font& font)
	:font(font)
{
	this->background.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	this->container.setSize(sf::Vector2f(static_cast<float>(vm.width) / 4.f, static_cast<float>(vm.height)));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(sf::Vector2f(static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f, 0.f));

	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(GUI::calcCharSize(vm, 46));
	this->menuText.setString("PAUSED");

	this->menuText.setPosition(sf::Vector2f(this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + GUI::p2pY(1.9f, vm)));
}

PauseMenu::PauseMenu(sf::VideoMode& vm, sf::Font& font, std::string text, sf::Color color, bool horiz)
	:font(font)
{
	this->background.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	this->container.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height) / 4.f));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(sf::Vector2f(0.f, static_cast<float>(vm.height) / 2.f - this->container.getSize().y / 2.f));

	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(GUI::calcCharSize(vm, 46));
	this->menuText.setFillColor(color);
	this->menuText.setString(text);

	this->menuText.setPosition(sf::Vector2f(this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + GUI::p2pY(1.9f, vm)));
}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
		delete it->second;
}

// Functions
std::map<std::string, GUI::Button*>& PauseMenu::GetButtons()
{
	return this->buttons;
}

const bool PauseMenu::IsButtonPressed(const std::string key)
{
	return this->buttons[key]->IsPressed();
}

void PauseMenu::AddButton(const std::string key, const float y, const float width, const float height, const unsigned charSize, const std::string text)
{
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new GUI::Button(
		x, y, width, height,
		&this->font, text, charSize,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50), // 150 30 241 - purple
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void PauseMenu::Update(const sf::Vector2i& mousePosWindow)
{
	for (auto& i : this->buttons)
	{
		i.second->Update(mousePosWindow);
	}
}

void PauseMenu::Render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& i : this->buttons)
		i.second->Render(target);

	target.draw(this->menuText);
}
