#include"stdafx.h"
#include "Swordsmen.h"

void Swordsmen::InitAnimation()
{
	this->animationComponent->AddAnimation("IDLE", 11.f, 0, 0, 5, 0, 65, 64);
	this->animationComponent->AddAnimation("WALK_DOWN", 11.f, 0, 0, 5, 0, 65, 64);
	this->animationComponent->AddAnimation("WALK_LEFT", 5.f, 0, 1, 5, 1, 65, 64);
	this->animationComponent->AddAnimation("WALK_RIGHT", 11.f, 0, 6, 5, 6, 65, 64);
	this->animationComponent->AddAnimation("WALK_UP", 11.f, 0, 2, 5, 2, 65, 64);

}

Swordsmen::Swordsmen(float posX, float posY, sf::Texture& texture_sheet, Entity& Player)
{

	//this->shape.setPosition(posX, posY);
	this->sprite.setScale(3.f, 3.f);
	this->damageTimerMax = 500;

	//this->CreateHitboxComponent(this->shape, 75.f, 73.f, 50.f, 53.f);
	//this->CreateMovementComponent(70.f, 350.f, 50.f);
	//this->CreateAnimationComponent(this->textureSheet);

	//this->follow = new AIFollow(*this, player);

	this->CreateHitboxComponent(this->sprite, 75.f, 73.f, 50.f, 53.f);
	this->CreateMovementComponent(200.f, 1600.f, 1000.f);
	this->CreateAnimationComponent(texture_sheet);
	this->CreateAttributeComponent(1);

	this->InitAnimation();

	this->follow = new AIFollow(*this, Player);
}

Swordsmen::~Swordsmen()
{
	//delete this->animationComponent;
	delete this->follow;
}

const sf::Vector2f& Swordsmen::GetPosition() const
{
	return this->sprite.getPosition();
}

const sf::Vector2f Swordsmen::GetCenter() const
{
	return this->sprite.getPosition() + sf::Vector2f(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f);
}

const float Swordsmen::GetDamage() const
{
	return 0.5f;
}

const bool& Swordsmen::GetDamageTimer()
{
	if (this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax)
	{
		this->damageTimer.restart();
		return true;
	}

	return false;
}

void Swordsmen::CreateAnimationComponent(sf::Texture& textureSheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, textureSheet);
}

void Swordsmen::SetScale(float x, float y)
{
	this->sprite.setScale(x, y);
}

void Swordsmen::SetPosition(float posX, float posY)
{
	this->sprite.setPosition(posX, posY);
}


void Swordsmen::UpdateAnimation(const float& dt)
{
	if (this->movementComponent->GetState(IDLE))
	{
		this->animationComponent->Play("IDLE", dt);
	}
	else if (this->movementComponent->GetState(MOVING_LEFT))
	{
		this->animationComponent->Play("WALK_LEFT", dt, this->movementComponent->GetVelocity().x, this->movementComponent->GetMaxVelocity());
	}
	else if (this->movementComponent->GetState(MOVING_RIGHT))
	{
		this->animationComponent->Play("WALK_RIGHT", dt, this->movementComponent->GetVelocity().x, this->movementComponent->GetMaxVelocity());
	}
	else if (this->movementComponent->GetState(MOVING_UP))
	{
		this->animationComponent->Play("WALK_UP", dt, this->movementComponent->GetVelocity().y, this->movementComponent->GetMaxVelocity());
	}
	else if (this->movementComponent->GetState(MOVING_DOWN))
	{
		this->animationComponent->Play("WALK_DOWN", dt, this->movementComponent->GetVelocity().y, this->movementComponent->GetMaxVelocity());
	}
}

void Swordsmen::CheckIsEnemiesInTileMap(Entity& Enemy)
{
	this->follow = new AIFollow(*this, Enemy);
}

void Swordsmen::Update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view)
{
	//this->movementComponent->Update(dt);
	//this->UpdateAnimation(dt);
	//this->animationComponent->Play("IDLE", dt);
	//this->hitboxComponent->Update();
	//this->follow->Update(dt);

	this->movementComponent->Update(dt);

	//this->UpdateAttack();

	this->UpdateAnimation(dt);

	this->hitboxComponent->Update();

	this->follow->Update(dt);
}

void Swordsmen::Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPosition)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", lightPosition);
		target.draw(this->sprite, shader);
	}
	else
		target.draw(this->sprite);

	this->hitboxComponent->Render(target);
}
