#pragma once

enum DAMAGE_STATES { DEFAULT_ATTACK = 0, DODGE, CRIT };

class AttributeComponent
{
public:
	// Variables
	float hp;

	int level;
	int exp;
	int expNext;
	int attributePoints;
	int strength;
	int vitality;
	int dexterity;
	int agility;
	int intelligence;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;

	short damageStates;

	// Constructor/Destructor
	AttributeComponent(int level);
	virtual ~AttributeComponent();

	// Functions
	std::string DebugPrint() const;
	void LoseHP(const float hp);
	void LoseEXP(const int exp);
	void GainHP(const int hp);
	void GainExp(const int exp);
	const bool IsDead() const;
	void UpdateStats(const bool reset);
	void UpdateLevel();
	void Update();
};

