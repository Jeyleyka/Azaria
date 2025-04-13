#include "stdafx.h"
#include "Chest.h"


void Chest::InitTexture(StateData* stateData)
{
	this->chestTexture.loadFromFile("Resources/Other/box.png");
	this->chest.setTexture(this->chestTexture);
	this->stateData = new StateData();
	this->chest.setPosition(stateData->gfxSettings->resolution.width / 2, stateData->gfxSettings->resolution.height / 2);
	this->chest.setScale(0.7f, 0.7f);
}

Chest::Chest(StateData* stateData)
{
	this->InitTexture(stateData);
}

Chest::~Chest()
{
}

const sf::Sprite& Chest::GetChest() const
{
	return this->chest;
}

void Chest::Render(sf::RenderTarget& target)
{
	target.draw(this->chest);
}
