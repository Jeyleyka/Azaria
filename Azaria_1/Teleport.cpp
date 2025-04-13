#include"stdafx.h"
#include "Teleport.h"

void Teleport::InitAnimation()
{
	this->animationComponent->AddAnimation("IDLE", 20.f, 0, 0, 3, 0, 50, 119);
}

Teleport::Teleport(float posX, float posY)
{
	if (!this->textureSheet.loadFromFile("Resources/Sprites/Teleport/teleport.png")) exit(07);
	this->shape.setTexture(this->textureSheet);

	this->shape.setPosition(posX, posY);

	this->CreateAnimationComponent(textureSheet);

	this->InitAnimation();
}

Teleport::~Teleport()
{
	delete this->animationComponent;
}

const sf::Vector2f Teleport::GetCenter() const
{
	return this->shape.getPosition() + sf::Vector2f(this->shape.getGlobalBounds().width / 2.f, this->shape.getGlobalBounds().height / 2.f);
}

const sf::FloatRect& Teleport::GetGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

void Teleport::CreateAnimationComponent(sf::Texture& textureSheet)
{
	this->animationComponent = new AnimationComponent(this->shape, textureSheet);
}

void Teleport::SetPosition(float posX, float posY)
{
	this->shape.setPosition(posX, posY);
}

void Teleport::Update(const float& dt)
{
	this->animationComponent->Play("IDLE", dt);
}

void Teleport::Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPosition)
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
