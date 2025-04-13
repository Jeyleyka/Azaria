#include "stdafx.h"
#include "PlayerGUI.h"

//Initializer functions
void PlayerGUI::InitFont()
{
	if (!this->font.loadFromFile("Fonts/font3.ttf")) exit(3);
}

void PlayerGUI::InitLevelBar()
{
	float width = GUI::p2pX(5.9f, this->vm);
	float height = GUI::p2pY(2.8f, this->vm);
	float x = GUI::p2pX(1.f, this->vm);
	float y = GUI::p2pY(1.9f, this->vm);

	this->levelBarBack.setSize(sf::Vector2f(width, height));
	this->levelBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->levelBarBack.setPosition(x, y);

	this->levelBarText.setFont(this->font);
	this->levelBarText.setCharacterSize(GUI::calcCharSize(this->vm, 90));
	this->levelBarText.setPosition(
		this->levelBarBack.getPosition().x + GUI::p2pX(0.53f, this->vm),
		this->levelBarBack.getPosition().y - GUI::p2pY(0.5f, this->vm));
}

void PlayerGUI::InitEXPBar()
{
	this->expBar = new GUI::ProgressBar(1.f, 5.7f, 11.9f, 2.1f, this->player->GetAttributeComponent()->expNext, sf::Color::Blue, 129, this->vm, &this->font);
}

void PlayerGUI::InitHPBar()
{
	this->hpBar = new GUI::ProgressBar(1.f, 8.3f, 10.4f, 2.8f, this->player->GetAttributeComponent()->hpMax, sf::Color::Red, 109, this->vm, &this->font);
}

void PlayerGUI::InitInventory()
{

}

// Constructor/Destructor
PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vm)
	: vm(vm)
{
	this->player = player;

	this->InitFont();
	this->InitLevelBar();
	this->InitEXPBar();
	this->InitHPBar();
	this->InitInventory();
}

PlayerGUI::~PlayerGUI()
{
	delete this->hpBar;
	delete this->expBar;
}

// Functions
void PlayerGUI::UpdateLevelBar()
{
	this->levelBarString = std::to_string(this->player->GetAttributeComponent()->level);
	this->levelBarText.setString("LV: " + this->levelBarString);
}

void PlayerGUI::UpdateEXPBar()
{
	this->expBar->Update(this->player->GetAttributeComponent()->exp);
}

void PlayerGUI::UpdateHPBar()
{
	this->hpBar->Update(this->player->GetAttributeComponent()->hp);
}

void PlayerGUI::UpdateInventory()
{

}

void PlayerGUI::Update(const float& dt)
{
	this->UpdateLevelBar();
	this->UpdateEXPBar();
	this->UpdateHPBar();
}

void PlayerGUI::RenderLevelBar(sf::RenderTarget& target)
{
	target.draw(this->levelBarBack);
	target.draw(this->levelBarText);
}

void PlayerGUI::RenderEXPBar(sf::RenderTarget& target)
{
	this->expBar->Render(target);
}

void PlayerGUI::RenderHPBar(sf::RenderTarget& target)
{
	this->hpBar->Render(target);
}

void PlayerGUI::RenderInventory(sf::RenderTarget& target)
{
	this->inventory->Render(target);
}

void PlayerGUI::Render(sf::RenderTarget& target)
{
	this->RenderLevelBar(target);
	this->RenderEXPBar(target);
	this->RenderHPBar(target);
	//this->RenderInventory(target);

	//if (this->inventory->IsPressed())
	//	this->player->RenderInventory(target);
}