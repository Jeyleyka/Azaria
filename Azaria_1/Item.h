#pragma once

enum ItemTypes { IT_DEFAULT = 0, IT_RANGEDWEAPON, IT_MELEEWEAPON };
enum ItemRarities { COMMON = 0, UNCOMMON, RARE, MYTHIC, LEGENDARY };

class Item
{
private:
	void InitVariables();

protected:
	// Variables
	unsigned short type;
	unsigned level;
	unsigned value;

public:

	// Constructor/Destructor
	Item(unsigned level, unsigned value);
	virtual ~Item();

	const short unsigned& GetType() const { return this->type; }
	const unsigned& GetLevel() const { return this->level; }
	const unsigned& GetValue() const { return this->value; }

	// Functions
	virtual Item* Clone() = 0;
};

