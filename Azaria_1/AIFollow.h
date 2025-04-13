#pragma once

#include "AIOption.h"

class AIFollow : public AIOption
{
private:

public:
	AIFollow(Entity& self, Entity& entity);
	~AIFollow();

	void Update(const float& dt);
};

