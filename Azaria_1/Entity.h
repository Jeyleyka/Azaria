#pragma once

#include"HitboxComponent.h"
#include"MovementComponent.h"
#include"AnimationComponent.h"
#include"AttributesComponent.h"
#include"SkillComponent.h"

enum ModifyTypes { DEF, COMB, FREEZ };

class Entity
{
private:
	// Initialization
	void InitVariables();

protected:
	// Variables
	sf::Sprite sprite;

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	AttributeComponent* attributeComponent;
	SkillComponent* skillComponent;

	 unsigned short typeOfModify;
public:
	// Constructor/Destructor
	Entity();
	virtual ~Entity();

	// Functions
	void SetTexture(sf::Texture& texture_sheet);
	void CreateHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	void CreateMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void CreateAnimationComponent(sf::Texture& textureSheet);
	void CreateAttributeComponent(const unsigned level);
	void CreateSkillComponent();
	void CreateAIComponent();

	virtual MovementComponent* GetMovementComponent();
	virtual AnimationComponent* GetAnimationComponent();
	virtual AttributeComponent* GetAttributeComponent();
	virtual SkillComponent* GetSkillComponent();

	virtual const sf::Vector2f& GetPosition() const;
	virtual const sf::Vector2f& GetSpritePosition() const;
	virtual const sf::Vector2f GetCenter() const;
	virtual const sf::Vector2f GetSpriteCenter() const;
	virtual const sf::Vector2i GetGridPosition(const int gridSizeI) const;
	virtual const sf::FloatRect GetGlobalBounds() const;
	virtual const sf::FloatRect GetNextPositionBounds(const float& dt) const;

	virtual void SetPosition(const float x, const float y);
	virtual void Move(const float dir_x, const float dir_y, const float& dt);
	virtual void StopVelocity();
	virtual void StopVelocityX();
	virtual void StopVelocityY();
	virtual const float GetDistance(const Entity& entity) const;
	virtual const float GetSpriteDistance(const Entity& entity) const;
	virtual void Update(const float& dt, sf::Vector2f& mousePosView, const sf::View& view) = 0;
	virtual void Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPosition) = 0;
};

