#pragma once
#include "RangedWeapon.h"

class RangedWeapon;

class Bow : public RangedWeapon
{
private:
	Arrow* arrow;
	//sf::RectangleShape rangeZone;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;

	int shootTimer;

public:
	Bow(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string textureFile, std::string arrowTexture);
	virtual ~Bow();

	virtual Bow* Clone();
	virtual void UpdateArrow();
	virtual void CollisionWithEnemy(Enemy* enemy);
	virtual void Update(const sf::Vector2f& mousePosView, const sf::Vector2f center, const sf::View& view);
	virtual void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr);
};

