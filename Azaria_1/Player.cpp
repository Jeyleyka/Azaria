#include "stdafx.h"
#include "Player.h"

//Initializer functions
void Player::InitVariables()
{
	this->initAttack = false;
	this->attacking = false;
	this->takeNewWeapon = false;
	this->levelUpdated = false;
	this->enemiesDead = false;
	this->weaponIsSword = false;
	this->updateBow = false;
	this->arrow = new Arrow("Resources/Sprites/Player/arrow_0.png");
	this->weapon = new Sword(1, 1, 3, 100, 20, "Resources/Sprites/Player/sword_0.png");
	this->weapon->Generate(3, 1);

	this->damageTimerMax = 500;

	this->keytime = 0.f;
	this->keytimeMax = 10.f;
	this->random = rand() % 2;
	this->weaponLevel = 0;
	this->currentLevel = 1;
	this->newLevel = 2;
}

void Player::InitComponents()
{

}

void Player::InitAnimations()
{
	this->animationComponent->AddAnimation("IDLE", 15.f, 0, 0, 3, 0, 32, 32);
	this->animationComponent->AddAnimation("WALK_DOWN", 11.f, 0, 0, 3, 0, 32, 32);
	this->animationComponent->AddAnimation("WALK_LEFT", 11.f, 0, 1, 3, 1, 32, 32);
	this->animationComponent->AddAnimation("WALK_RIGHT", 11.f, 0, 2, 3, 2, 32, 32);
	this->animationComponent->AddAnimation("WALK_UP", 11.f, 0, 3, 3, 3, 32, 32);
	//this->animationComponent->AddAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 114);
	//this->animationComponent->AddAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 114);
	//this->animationComponent->AddAnimation("WALK_LEFT", 11.f, 4, 1, 7, 1, 64, 114);
	//this->animationComponent->AddAnimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 114);
	//this->animationComponent->AddAnimation("WALK_UP", 11.f, 12, 1, 15, 1, 64, 114);
	//this->animationComponent->AddAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 114);
}

Player::Player()
{
}

//Constructors / Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet, sf::VideoMode& vm)
{
	this->InitVariables();

	this->CreateHitboxComponent(this->sprite, 16.f, 26.f, 32.f, 38.f);
	this->CreateMovementComponent(200.f, 1600.f, 1000.f);
	this->CreateAnimationComponent(texture_sheet);
	this->CreateAttributeComponent(1);
	this->CreateSkillComponent();

	this->sprite.setScale(2.5f, 2.5f);

	this->SetPosition(x, y);
	this->InitAnimations();
}

Player::~Player()
{
	delete this->weapon;
	delete this->arrow;
	//delete this->sword;
}

//Functions
AttributeComponent* Player::GetAttributeComponent()
{
	return this->attributeComponent;
}

const bool& Player::GetInitAttack() const
{
	return this->initAttack;
}

const bool& Player::GetUpdateBow() const
{
	return this->updateBow;
}

const short& Player::GetNewLevel() const
{
	return this->newLevel;
}

const short& Player::GetWeaponLevel() const
{
	return this->weaponLevel;
}

const short& Player::GetCurrentLevel() const
{
	return this->currentLevel;
}

const bool& Player::GetNewWeapon() const
{
	return this->takeNewWeapon;
}

const unsigned& Player::GetRandom() const
{
	return this->random;
}

const bool& Player::GetEnemiesDead() const
{
	return this->enemiesDead;
}

const bool& Player::GetDamageTimer()
{
	if (this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax)
	{
		this->damageTimer.restart();
		return true;
	}

	return false;
}

const unsigned Player::GetDamage() const
{
	return rand() % (this->attributeComponent->damageMax + this->weapon->GetDamageMax() - (this->attributeComponent->damageMin +
		this->weapon->GetDamageMin()) + 1) + (this->attributeComponent->damageMin + this->weapon->GetDamageMin());
}

const bool& Player::InventoryGetOpen() const
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		return true;

	return false;
}

const bool& Player::WeaponIsSword() const
{
	return this->weaponIsSword;
}

const bool Player::GetKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

const unsigned short& Player::GetTypeOfModify() const
{
	return this->typeOfModify;
}

void Player::SetInitAttack(const bool initAttack)
{
	this->initAttack = initAttack;
}

Weapon* Player::GetWeapon() const
{
	return this->weapon;
}

const std::string Player::ToStringCharacterTab() const
{
	std::stringstream ss;
	const AttributeComponent* ac = this->attributeComponent;
	const Weapon* w = this->weapon;

	ss << "Level: " << ac->level << "\n"
		<< "Exp: " << ac->exp << "\n"
		<< "Exp next: " << ac->expNext << "\n"
		<< "Weapon type: " << w->GetType() << "\n"
		<< "Weapon level: " << w->GetLevel() << "\n"
		<< "Weapon value: " << w->GetValue() << "\n";

	return ss.str();
}

void Player::LoseHP(const int hp)
{
	this->attributeComponent->LoseHP(hp);
}

void Player::LoseEXP(const int exp)
{
	this->attributeComponent->LoseHP(exp);
}

void Player::GainHP(const int hp)
{
	this->attributeComponent->GainHP(hp);
}

void Player::GainEXP(const int exp)
{
	this->attributeComponent->GainExp(exp);
}

void Player::SetNewWeapon()
{
	if (this->takeNewWeapon)
		this->takeNewWeapon = false;
	else
		this->takeNewWeapon = true;

	this->levelUpdated = true;
}

void Player::SetModifier(unsigned short modify)
{
	delete this->weapon;

	this->weapon = new Sword(2, 1, 2, 100, 20, "Resources/Sprites/Player/sword_" + std::to_string(this->weaponLevel) + ".png", modify);
	this->weapon->SetRange(70);
	this->typeOfModify = modify;

	//std::cout << "Type in player: " << this->typeOfModify << std::endl;

	this->weaponIsSword = true;

	//std::cout << "after weapon: " << this->weapon << std::endl;

	this->takeNewWeapon = true;
}

void Player::SetUpdateBowTrue()
{
	this->updateBow = true;
}

void Player::SetEnemiesDead()
{
	if (this->enemiesDead)
		this->enemiesDead = false;
	else
		this->enemiesDead = true;
}

void Player::IncreaseCurrentLevel(int level)
{
	this->currentLevel += level;

	//if (this->currentLevel % 5 == 0)
	//	this->weaponLevel += level;
}

void Player::IncreaseWeaponLevel(int level)
{
	this->weaponLevel += level;
}

void Player::SetCurrentLevel(int level)
{
	this->currentLevel = level;
}

void Player::SetNewLevel(int level)
{
	this->newLevel = level;
}

void Player::IncreaseNewLevel(int level)
{
	this->newLevel += level;
}

void Player::UpdateAnimation(const float& dt)
{
	if (this->attacking)
	{

	}

	if (this->movementComponent->GetState(IDLE))
		this->animationComponent->Play("IDLE", dt);
	else if (this->movementComponent->GetState(MOVING_LEFT))
		this->animationComponent->Play("WALK_LEFT", dt, this->movementComponent->GetVelocity().x, this->movementComponent->GetMaxVelocity());
	else if (this->movementComponent->GetState(MOVING_RIGHT))
		this->animationComponent->Play("WALK_RIGHT", dt, this->movementComponent->GetVelocity().x, this->movementComponent->GetMaxVelocity());
	else if (this->movementComponent->GetState(MOVING_UP))
		this->animationComponent->Play("WALK_UP", dt, this->movementComponent->GetVelocity().y, this->movementComponent->GetMaxVelocity());
	else if (this->movementComponent->GetState(MOVING_DOWN))
		this->animationComponent->Play("WALK_DOWN", dt, this->movementComponent->GetVelocity().y, this->movementComponent->GetMaxVelocity());
}

void Player::UpdateInventory()
{

}

void Player::UpdateSword()
{
	delete this->weapon;
	this->weapon = NULL;

	//std::cout << "weapon: " << this->weapon << std::endl;

	delete this->arrow;
	this->arrow = NULL;

	this->weapon = new Sword(2, 2, 4, 100, 20, "Resources/Sprites/Player/sword_" + std::to_string(this->weaponLevel) + ".png");
	this->weapon->SetRange(70);
	this->weaponIsSword = true;

	//std::cout << "after weapon: " << this->weapon << std::endl;

	this->takeNewWeapon = true;
}

void Player::UpdateBow()
{
	delete this->weapon;
	this->weapon = NULL;

	//std::cout << "weapon: " << this->weapon << std::endl;

	delete this->arrow;
	this->arrow = NULL;

	this->weapon = new Bow(2, 1, 3, 100, 20, "Resources/Sprites/Player/bow_" + std::to_string(this->weaponLevel) + ".png", "Resources/Sprites/Player/arrow_" + std::to_string(this->weaponLevel) + ".png");
	this->arrow = new Arrow("Resources/Sprites/Player/arrow_" + std::to_string(this->weaponLevel) + ".png");

	//std::cout << "after weapon: " << this->weapon << std::endl;

	this->takeNewWeapon = true;
}

void Player::Update(const float& dt, sf::Vector2f& mousePosView, const sf::View& view)
{
	this->movementComponent->Update(dt);

	this->UpdateAnimation(dt);

	this->hitboxComponent->Update();
	//this->UpdateInventory();

	
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		this->UpdateWeapon(mousePosView, sf::Vector2f(this->GetSpriteCenter().x, this->GetSpriteCenter().y + 5.f), view);*/
}

void Player::Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPosition)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", lightPosition);
		target.draw(this->sprite, shader);

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", lightPosition);
		this->weapon->Render(target, shader);
	}
	else
	{
		target.draw(this->sprite);
		this->weapon->Render(target);
	}

	//this->RenderInventory(target);

		//this->hitboxComponent->Render(target);
}
