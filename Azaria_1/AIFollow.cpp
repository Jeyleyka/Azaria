#include "stdafx.h"
#include "AIFollow.h"

AIFollow::AIFollow(Entity& self, Entity& entity)
	: AIOption(self, entity)
{

}

AIFollow::~AIFollow()
{
}

void AIFollow::Update(const float& dt)
{
	sf::Vector2f moveVec;
	bool isMoving = true;

	moveVec.x = entity.GetPosition().x - self.GetPosition().x;
	moveVec.y = entity.GetPosition().y - self.GetPosition().y;

	float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

	moveVec /= vecLength;

	if (self.GetPosition().x != entity.GetPosition().x && isMoving)
		self.Move(moveVec.x, moveVec.y, dt);

	//if (self.GetGlobalBounds().intersects(sf::FloatRect(obstaclePosition, obstacleSize))) {
	//	isMoving = false;
	//}
	//else {
	//	isMoving = true;
	//}
}
