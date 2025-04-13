#include"stdafx.h"
#include "Coin.h"

void Coin::InitAnimation()
{
	this->animationComponent->AddAnimation("IDLE", 10.f, 0, 0, 7, 0, 32, 32);
}

Coin::Coin(float posX, float posY)
{
	if (!this->textureSheet.loadFromFile("Resources/Sprites/Coin/coin-test-2.png")) exit(07);
	this->shape.setTexture(this->textureSheet);

	this->shape.setPosition(posX, posY);

	this->CreateAnimationComponent(textureSheet);

	this->InitAnimation();
}

Coin::~Coin()
{
	delete this->animationComponent;
}

const sf::Vector2f Coin::GetCenter() const
{
	return this->shape.getPosition() + sf::Vector2f(this->shape.getGlobalBounds().width / 2.f, this->shape.getGlobalBounds().height / 2.f);
}

const sf::FloatRect& Coin::GetGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

void Coin::CreateAnimationComponent(sf::Texture& textureSheet)
{
	this->animationComponent = new AnimationComponent(this->shape, textureSheet);
}

void Coin::SetScale(float x, float y)
{
	this->shape.setScale(x, y);
}

void Coin::SetPosition(float posX, float posY)
{
	this->shape.setPosition(posX, posY);
}

void Coin::Update(const float& dt)
{
	this->animationComponent->Play("IDLE", dt);
}

void Coin::Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPosition)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", lightPosition);
		target.draw(this->shape, shader);
	}
	else
		target.draw(this->shape);
}
