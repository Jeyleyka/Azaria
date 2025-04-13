#include"stdafx.h"
#include "Entity.h"

void Entity::InitVariables()
{
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
	this->animationComponent = NULL;
	this->attributeComponent = NULL;
	this->skillComponent = NULL;
	this->typeOfModify == ModifyTypes::DEF;
}

Entity::Entity()
{
	this->InitVariables();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->attributeComponent;
	delete this->skillComponent;
}

// Functions
void Entity::SetTexture(sf::Texture& texture_sheet)
{
	this->sprite.setTexture(texture_sheet);
}

void Entity::CreateHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::CreateMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::CreateAnimationComponent(sf::Texture& textureSheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, textureSheet);
}

void Entity::CreateAttributeComponent(const unsigned level)
{
	this->attributeComponent = new AttributeComponent(level);
}

void Entity::CreateSkillComponent()
{
	this->skillComponent = new SkillComponent();
}

void Entity::CreateAIComponent()
{
}

MovementComponent* Entity::GetMovementComponent()
{
	return this->movementComponent;
}

AnimationComponent* Entity::GetAnimationComponent()
{
	return this->animationComponent;
}

AttributeComponent* Entity::GetAttributeComponent()
{
	return this->attributeComponent;
}

SkillComponent* Entity::GetSkillComponent()
{
	return this->skillComponent;
}

const sf::Vector2f& Entity::GetPosition() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->GetPosition();

	return this->sprite.getPosition();
}

const sf::Vector2f& Entity::GetSpritePosition() const
{
	return this->sprite.getPosition();
}

const sf::Vector2f Entity::GetCenter() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->GetPosition() + sf::Vector2f(this->hitboxComponent->GetGlobalBounds().width / 2.f,
			this->hitboxComponent->GetGlobalBounds().height / 2.f);

	return this->sprite.getPosition() + sf::Vector2f(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f);
}

const sf::Vector2f Entity::GetSpriteCenter() const
{
	return this->sprite.getPosition() + sf::Vector2f(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f);
}

const sf::Vector2i Entity::GetGridPosition(const int gridSizeI) const
{
	if (this->hitboxComponent)
		return sf::Vector2i(
			static_cast<int>(this->hitboxComponent->GetPosition().x) / gridSizeI,
			static_cast<int>(this->hitboxComponent->GetPosition().y) / gridSizeI);

	return sf::Vector2i(
		static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
		static_cast<int>(this->sprite.getPosition().y) / gridSizeI);
}

const sf::FloatRect Entity::GetGlobalBounds() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->GetGlobalBounds();

	return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::GetNextPositionBounds(const float& dt) const
{
	if (this->hitboxComponent && this->movementComponent)
		return this->hitboxComponent->GetNextPosition(this->movementComponent->GetVelocity() * dt);


	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

void Entity::SetPosition(const float x, const float y)
{
	if (this->hitboxComponent)
		this->hitboxComponent->SetPosition(x, y);
	else
		this->sprite.setPosition(x, y);
}

void Entity::Move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent)
		this->movementComponent->Move(dir_x, dir_y, dt);

	if (this->skillComponent)
		this->skillComponent->GainExp(ENDURANCE, 1);
}

void Entity::StopVelocity()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocity();

}

void Entity::StopVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityX();
}

void Entity::StopVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}

const float Entity::GetDistance(const Entity& entity) const
{
	return sqrt(powf(this->GetCenter().x - entity.GetCenter().x, 2) + powf(this->GetCenter().y - entity.GetCenter().y, 2));
}

const float Entity::GetSpriteDistance(const Entity& entity) const
{
	return sqrt(powf(this->GetSpriteCenter().x - entity.GetSpriteCenter().x, 2) + powf(this->GetSpriteCenter().y - entity.GetSpriteCenter().y, 2));
}
