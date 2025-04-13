#pragma once
//#include"LevelsState.h"
#include "Item.h"
#include"Enemy.h"

class Arrow
{
public:
	//sf::CircleShape shape;
	//LevelsState* level;
	sf::Sprite shape;
	sf::Texture texture;
	sf::Vector2f currentVelocity;

	float maxSpeed;

	Arrow()
		: currentVelocity(0.f, 0.f), maxSpeed(15.f)
	{

	}

	Arrow(std::string path)
		: currentVelocity(0.f, 0.f), maxSpeed(15.f)
	{
		//this->shape.setRadius(radius);
		//this->shape.setFillColor(sf::Color::Red);
		if (!this->texture.loadFromFile(path)) exit(02);
		this->shape.setTexture(this->texture);
	}

	void UpdateArrow()
	{
		this->texture.loadFromFile("Resources/Sprites/Player/arrow_2.png");
		this->shape.setTexture(this->texture);
	}
};

enum TypesOfModifeirs {NONE, COMBUSTION, FREEZING};

class Weapon : public Item
{
private:
	void InitVariables();

protected:
	// Variables
	sf::Sprite weaponSprite;
	sf::Texture weaponTexture;
	sf::Clock attackTimer;
	sf::Int32 attackTimerMax;

	float keytime;
	float keytimeMax;
	unsigned range;
	unsigned damageMin;
	unsigned damageMax;

	unsigned short typeModify;

	bool dodge;

public:
	std::vector<Arrow> arrows;

	// Constructor/Destructor
	Weapon(unsigned level, unsigned value, std::string textureFile);
	Weapon(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string textureFile, unsigned short modify = TypesOfModifeirs::NONE);
	virtual ~Weapon();

	// Functions
	const bool GetKeytime();
	const unsigned& GetDamageMin() const;
	const unsigned& GetDamageMax() const;
	const unsigned GetDamage() const;
	const unsigned GetRange() const;
	const unsigned short& GetModifiers() const;
	const sf::FloatRect& GetGlobalBoundsArrow() const;
	const std::vector<Arrow>& GetArrowArray() const;
	bool GetIntersectWithEnemy(Enemy* enemy);

	void SetRange(unsigned range);
	void SetModifier(unsigned short modify);
	void RemoveArrow();
	const bool GetAttackTimer();
	virtual Weapon* Clone() = 0;
	virtual void Generate(const unsigned levelMax, const unsigned levelMin) = 0;
	virtual void Update(const sf::Vector2f& mousePosView, const sf::Vector2f center, const sf::View& view) = 0;
	virtual void Render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

