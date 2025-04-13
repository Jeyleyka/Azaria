#include "stdafx.h"
#include "SkillComponent.h"

SkillComponent::SkillComponent()
{
	this->skills.push_back(Skill(HEALTH));
	this->skills.push_back(Skill(ATTACK));
	this->skills.push_back(Skill(ACCURACY));
	this->skills.push_back(Skill(ENDURANCE));
}


SkillComponent::~SkillComponent()
{
}

// Functions
const int SkillComponent::GetSkill(const int skill) const
{
	if (skills.empty() || skill < 0 || skill >= this->skills.size())
		throw("NOT_EXISTS_SKILL_NUMBER: " + skill);
	else
		return this->skills[skill].GetLevel();
}

const void SkillComponent::GainExp(const int skill, const int exp)
{
	if (skills.empty() || skill < 0 || skill >= this->skills.size())
		throw("NOT_EXISTS_SKILL_NUMBER: " + skill);
	else
		this->skills[skill].GainExp(exp);
}
