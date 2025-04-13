#pragma once
#include "MeleeWeapon.h"

class MeleeWeapon;

class Sword : public MeleeWeapon
{
private:
	// Variables

public:
	// Constructor/Destructor
	Sword(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string textureFile, unsigned short modify = TypesOfModifeirs::NONE);
	virtual ~Sword();

	// Functions
	virtual Sword* Clone();
	virtual void Update(const sf::Vector2f& mousePosView, const sf::Vector2f center, const sf::View& view);
	virtual void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr);
};

