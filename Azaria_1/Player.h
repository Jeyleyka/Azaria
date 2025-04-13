#pragma once

#include "Entity.h"
#include"Sword.h"
#include"Bow.h"

class Player : public Entity
{
private:
	//Variables
	//Sword* sword;
	Weapon* weapon;
	Arrow* arrow;

	sf::Clock damageTimer;
	sf::Int32 damageTimerMax;

	unsigned random;

	float keytime;
	float keytimeMax;

	short weaponLevel;
	short currentLevel;
	short newLevel;

	bool initAttack;
	bool attacking;
	bool takeNewWeapon;
	bool levelUpdated;
	bool enemiesDead;
	bool weaponIsSword;
	bool updateBow;

	//Initializer functions
	void InitVariables();
	void InitComponents();
	void InitAnimations();

public:
	// Constructor/Destructor
	Player();
	Player(float x, float y, sf::Texture& texture_sheet, sf::VideoMode& vm);
	virtual ~Player();

	//Functions
	AttributeComponent* GetAttributeComponent();
	const short& GetNewLevel() const;
	const short& GetWeaponLevel() const;
	const short& GetCurrentLevel() const;
	const bool& GetInitAttack() const;
	const bool& GetUpdateBow() const;
	const bool& GetNewWeapon() const;
	const unsigned& GetRandom() const;
	const bool& GetEnemiesDead() const;
	const bool& GetDamageTimer();
	const bool& InventoryGetOpen() const;
	const bool& WeaponIsSword() const;
	const bool GetKeytime();
	const unsigned short& GetTypeOfModify() const;
	const unsigned GetDamage() const;
	void SetInitAttack(const bool initAttack);
	Weapon* GetWeapon() const;
	const std::string ToStringCharacterTab() const;
	void LoseHP(const int hp);
	void LoseEXP(const int exp);
	void GainHP(const int hp);
	void GainEXP(const int exp);
	void SetNewWeapon();
	void SetModifier(unsigned short modify);
	void SetUpdateBowTrue();
	void SetEnemiesDead();
	void IncreaseCurrentLevel(int level);
	void IncreaseWeaponLevel(int level);
	void SetCurrentLevel(int level);
	void SetNewLevel(int level);
	void IncreaseNewLevel(int level);
	void UpdateAnimation(const float& dt);
	void UpdateInventory();
	void UpdateSword();
	void UpdateBow();
	void Update(const float& dt, sf::Vector2f& mousePosView, const sf::View& view);
	void Render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f lightPosition = sf::Vector2f());
};