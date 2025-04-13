#pragma once
#include "Weapon.h"

class MeleeWeapon : public Weapon
{
private:
	// Variables

protected:
	sf::Sprite weaponSprite;
	sf::Texture weaponTexture;

	int damageMin;
	int damageMax;
	bool attacking;

public:
	// Constructor/Destructor
	MeleeWeapon(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string textureFile);
	virtual ~MeleeWeapon();

	virtual MeleeWeapon* Clone() = 0;
	virtual void Generate(const unsigned levelMax, const unsigned levelMin);
	virtual void Update(const sf::Vector2f& mousePosView, const sf::Vector2f center, const sf::View& view) = 0;
	virtual void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

