#include"stdafx.h"
#include "Dealer.h"

void Dealer::InitAnimation()
{
	this->animationComponent->AddAnimation("IDLE", 10.f, 0, 0, 13, 0, 64, 64);
}

Dealer::Dealer(float posX, float posY, float greetingPosX, float greetingPosY)
{
	this->openShop = false;

	if (!this->textureSheet.loadFromFile("Resources/Sprites/Dealer/dealer.png")) exit(07);
	this->shape.setTexture(this->textureSheet);

	this->shape.setPosition(posX, posY);

	this->CreateAnimationComponent(textureSheet);

	this->greetingBg.setSize(sf::Vector2f(295.f, 105.f));
	this->greetingBg.setPosition(greetingPosX, greetingPosY);
	this->greetingBg.setFillColor(sf::Color(39, 38, 37, 240));

	if (!this->font.loadFromFile("Fonts/font3.ttf")) exit(9);

	this->pressButton.setFont(this->font);
	this->pressButton.setFillColor(sf::Color::Green);
	this->pressButton.setCharacterSize(16);
	this->pressButton.setPosition(greetingPosX + 5.f, greetingPosY + 75.f);
	this->pressButton.setString("Press F to open the store");

	this->greetingText.setFont(this->font);
	this->greetingText.setCharacterSize(16);
	this->greetingText.setPosition(greetingPosX + 5.f, greetingPosY + 5.f);
	this->greetingText.setString("Greetings to you, wanderer,\ni advise you not to pass by me\nbecause my goods will help you\nsurvive in this world");

	this->InitAnimation();
}

Dealer::~Dealer()
{
	delete this->animationComponent;
}

const sf::Vector2f& Dealer::GetPosition() const
{
	return this->shape.getPosition();
}

const sf::Vector2f& Dealer::GetCenter() const
{
	return this->shape.getPosition() + sf::Vector2f(this->shape.getGlobalBounds().width / 2.f, this->shape.getGlobalBounds().height / 2.f);
}

const sf::FloatRect& Dealer::GetGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

void Dealer::CreateAnimationComponent(sf::Texture& textureSheet)
{
	this->animationComponent = new AnimationComponent(this->shape, textureSheet);
}

void Dealer::SetScale(float x, float y)
{
	this->shape.setScale(x, y);
}

void Dealer::SetPosition(float posX, float posY)
{
	this->shape.setPosition(posX, posY);
}

void Dealer::SetShopTrue()
{
	this->openShop = true;
}

void Dealer::SetShopFalse()
{
	this->openShop = false;
}

void Dealer::Update(const float& dt)
{
	this->animationComponent->Play("IDLE", dt);
}

void Dealer::Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPosition)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", lightPosition);
		target.draw(this->shape, shader);
	}
	else
		target.draw(this->shape);

	if (this->openShop)
	{
		target.draw(this->greetingBg);
		target.draw(this->greetingText);
		target.draw(this->pressButton);
	}
}
