#pragma once
#include "Weapon.h"

class RangedWeapon : public Weapon
{
private:

public:
	RangedWeapon(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string textureFile);
	virtual ~RangedWeapon();

	// Functions
	virtual RangedWeapon* Clone() = 0;
	virtual void Generate(const unsigned levelMax, const unsigned levelMin);
	virtual void Update(const sf::Vector2f& mousePosView, const sf::Vector2f center, const sf::View& view) = 0;
	virtual void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

