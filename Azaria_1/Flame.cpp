#include"stdafx.h"
#include "Flame.h"

void Flame::InitAnimation()
{
	this->animationComponent->AddAnimation("IDLE", 10.f, 0, 0, 7, 0, 24, 32);
}

Flame::Flame(float posX, float posY)
{
	if (!this->textureSheet.loadFromFile("Resources/Sprites/Flame/flame.png")) exit(07);
	this->shape.setTexture(this->textureSheet);

	this->shape.setPosition(posX, posY);

	this->shape.setScale(1.5f, 1.5f);

	this->CreateAnimationComponent(textureSheet);

	this->InitAnimation();
}

Flame::~Flame()
{
	delete this->animationComponent;
}

const sf::Vector2f Flame::GetCenter() const
{
	return this->shape.getPosition() + sf::Vector2f(this->shape.getGlobalBounds().width / 2.f, this->shape.getGlobalBounds().height / 2.f);
}

const sf::FloatRect& Flame::GetGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

void Flame::CreateAnimationComponent(sf::Texture& textureSheet)
{
	this->animationComponent = new AnimationComponent(this->shape, textureSheet);
}

void Flame::SetScale(float x, float y)
{
	this->shape.setScale(x, y);
}

void Flame::SetPosition(float posX, float posY)
{
	this->shape.setPosition(posX, posY);
}

void Flame::SetPosition(sf::Vector2f& pos)
{
	this->shape.setPosition(pos);
}

void Flame::Update(const float& dt)
{
	this->animationComponent->Play("IDLE", dt);
}

void Flame::Render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
