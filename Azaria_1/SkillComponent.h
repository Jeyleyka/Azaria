#pragma once

enum SKILLS { HEALTH = 0, ATTACK, ACCURACY, ENDURANCE };

class SkillComponent
{
private:
	class Skill
	{
	private:
		int type;
		int level;
		int levelCap;
		int exp;
		int expNext;

	public:
		Skill(int type)
		{
			this->type = type;
			this->level = 1;
			this->levelCap = 100;
			this->exp = 0;
			this->expNext = 100;
		}
		~Skill() {}

		// Functions
		inline const int& GetType() const { return this->type; }
		inline const int& GetLevel() const { return this->level; }
		inline const int& GetExp() const { return this->exp; }
		inline const int& GetExpNext() const { return this->expNext; }

		void SetLevel(const int level) { this->level = level; }
		void SetLevelCap(const int levelCap) { this->levelCap = levelCap; }

		void GainExp(const int exp)
		{
			this->exp += exp;
			this->UpdateLevel();
		}

		void LoseExp(const int exp)
		{
			this->exp -= exp;
		}

		void UpdateLevel(const bool up = true)
		{
			if (up)
			{
				if (this->level < this->levelCap)
				{
					while (this->exp >= this->expNext)
					{
						if (this->level < this->levelCap)
						{
							++this->level;
							this->expNext = static_cast<int>(std::pow(this->level, 2)) + this->level * 10 + this->level * 2;
						}
					}
				}
			}
			else
			{
				if (this->level > 0)
				{
					while (this->exp < 0)
					{
						if (this->level > 0)
						{
							--this->level;
							this->expNext = static_cast<int>(std::pow(this->level, 2)) + this->level * 10 + this->level * 2;
						}
					}
				}
			}
		}

		void Update()
		{

		}
	};

	// Variables
	std::vector<Skill> skills;

public:
	// Constructor/Destructor
	SkillComponent();
	virtual ~SkillComponent();

	// Functions
	const int GetSkill(const int skill) const;
	const void GainExp(const int skill, const int exp);
};

