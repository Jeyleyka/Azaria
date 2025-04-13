#include "stdafx.h"
#include "Bird.h"

//Initializer functions
void Bird::InitVariables()
{
	this->flame = new Flame(0.f, 0.f);
	this->showComb = false;
}

void Bird::InitAnimations()
{
	this->animationComponent->AddAnimation("IDLE", 25.f, 0, 0, 2, 0, 61, 57);
	this->animationComponent->AddAnimation("WALK_DOWN", 11.f, 0, 0, 2, 0, 61, 57);
	this->animationComponent->AddAnimation("WALK_LEFT", 11.f, 0, 1, 2, 1, 61, 57);
	this->animationComponent->AddAnimation("WALK_RIGHT", 11.f, 0, 2, 2, 2, 61, 57);
	this->animationComponent->AddAnimation("WALK_UP", 11.f, 0, 3, 2, 3, 61, 57);
	//this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 61, 57);
}

void Bird::InitAI()
{

}

void Bird::InitGUI()
{
	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setSize(sf::Vector2f(60.f, 10.f));
	this->hpBar.setPosition(this->sprite.getPosition());
}

//Constructors / Destructors
Bird::Bird(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& Player)
	: Enemy(enemy_spawner_tile)
{
	this->InitGUI();

	this->CreateHitboxComponent(this->sprite, 15.f, 15.f, 30.f, 30.f);
	this->CreateMovementComponent(250.f, 350.f, 50.f);
	this->CreateAnimationComponent(texture_sheet);
	this->CreateAttributeComponent(1);

	this->GenerateAttributes(this->attributeComponent->level);

	this->SetPosition(x, y);
	this->InitAnimations();

	this->InitVariables();

	this->follow = new AIFollow(*this, Player);
}


Bird::~Bird()
{
	delete this->follow;
	delete this->flame;
}

void Bird::UpdateAnimation(const float& dt)
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

	if (this->damageTimer.getElapsedTime().asMilliseconds() <= this->damageTimerMax)
	{
		this->sprite.setColor(sf::Color::Red);

		if (this->typeOfModify == ModifyTypes::COMB)
			this->showComb = true;
		else if (this->typeOfModify == ModifyTypes::FREEZ)
			this->showFreez = true;

		if (this->showComb)
		{
			this->flame->SetPosition(this->sprite.getPosition().x + 10.f, this->sprite.getPosition().y + 5.f);
			this->flame->Update(dt);
			this->LoseHP(0.02f);
		}
		else if (this->showFreez)
		{
			this->sprite.setColor(sf::Color::Blue);
			this->iceSprite.setPosition(this->sprite.getPosition().x + 10.f, this->sprite.getPosition().y + 5.f);
			this->movementComponent->SetMaxVelocity(100.f);
			this->LoseHP(0.02f);
		}
	}
	else
	{
		this->showComb = false;
		this->showFreez = false;
		this->sprite.setColor(sf::Color::White);
		this->movementComponent->SetMaxVelocity(250.f);
	}
}

void Bird::Update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view)
{
	Enemy::Update(dt, mouse_pos_view, view);

	this->movementComponent->Update(dt);

	//Update GUI REMOVE THIS!!!!
	this->hpBar.setSize(sf::Vector2f(60.f * (static_cast<float>(this->attributeComponent->hp) / this->attributeComponent->hpMax), 10.f));
	this->hpBar.setPosition(this->sprite.getPosition());

	//this->UpdateAttack();

	this->UpdateAnimation(dt);

	this->hitboxComponent->Update();

	this->follow->Update(dt);
}

void Bird::Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		target.draw(this->sprite, shader);
	}
	else
	{
		target.draw(this->sprite);
	}

	target.draw(this->hpBar);

	if (this->showComb)
		this->flame->Render(target);

	if (this->showFreez)
		target.draw(this->iceSprite);

	//this->hitboxComponent->Render(target);
}