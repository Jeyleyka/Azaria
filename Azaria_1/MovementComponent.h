#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

enum movement_states { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

	//Initializer functions

public:
	MovementComponent(sf::Sprite& sprite,
		float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const float& GetMaxVelocity() const;
	const sf::Vector2f& GetVelocity() const;

	//Functions
	const bool GetState(const short unsigned state) const;
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();
	void SetMaxVelocity(float velocity);
	void Move(const float x, const float y, const float& dt);
	void Update(const float& dt);
};

#endif