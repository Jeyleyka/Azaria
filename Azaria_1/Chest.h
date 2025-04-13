#pragma once

#include"State.h"
#include"AnimationComponent.h"

class Chest
{
private:
	sf::Sprite chest;
	sf::Texture chestTexture;
	StateData* stateData;
	AnimationComponent* animationComponent;

	void InitTexture(StateData* stateData);
public:

	Chest(StateData* stateData);
	virtual ~Chest();

	const sf::Sprite& GetChest() const;
	void Render(sf::RenderTarget& target);
};

