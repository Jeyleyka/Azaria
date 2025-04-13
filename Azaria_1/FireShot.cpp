#include"stdafx.h"
#include "FireShot.h"

void FireShot::InitAnimation()
{
	this->animationComponent->AddAnimation("IDLE", 7.f, 0, 0, 67, 8, 105, 100);
	this->animationComponent->AddAnimation("INTERSECTION", 13.f, 0, 1, 2, 1, 88, 100);
}

FireShot::FireShot(float posX, float posY, float angle)
{
	this->offsetX = 0.f;
	this->offsetY = 0.f;
	this->explosion = false;

	if (!this->textureSheet.loadFromFile("Resources/Sprites/FireShot/fire.png")) exit(07);
	this->shape.setTexture(this->textureSheet);

	//this->shape.setOrigin(this->shape.getLocalBounds().width / 2.f, this->shape.getLocalBounds().height / 2.f);

	this->velocity.x = std::cos(angle) * 5.f;
	this->velocity.y = std::sin(angle) * 5.f;

	std::cout << "angle: " << angle * 180.f / 3.14f << std::endl;

	//if (angle * 180.f / 3.14f > -40.f && angle * 180.f / 3.14f < 30.f)
	//{
	//	this->offsetY = -50.f;
	//	this->offsetX = 0.f;
	//}

	//if (angle * 180.f / 3.14f < -40.f && angle * 180.f / 3.14f > -110.f)
	//{
	//	this->offsetY = -50.f;
	//	this->offsetX = -20.f;
	//}

	this->shape.setRotation(angle * 180.f / 3.1415f);
	this->shape.setPosition(posX, posY);

	this->CreateAnimationComponent(textureSheet);

	this->InitAnimation();
}

FireShot::~FireShot()
{
	delete this->animationComponent;
}

const sf::Vector2f FireShot::GetCenter() const
{
	return this->shape.getPosition() + sf::Vector2f(this->shape.getGlobalBounds().width / 2.f, this->shape.getGlobalBounds().height / 2.f);
}

const sf::FloatRect& FireShot::GetGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

void FireShot::CreateAnimationComponent(sf::Texture& textureSheet)
{
	this->animationComponent = new AnimationComponent(this->shape, textureSheet);
}

void FireShot::SetScale(float x, float y)
{
	this->shape.setScale(x, y);
}

void FireShot::SetPosition(float posX, float posY)
{
	this->shape.setPosition(posX, posY);
}

void FireShot::Update(const float& dt)
{
	this->animationComponent->Play("IDLE", dt);
	this->shape.move(velocity);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		this->explosion = true;

	if (this->explosion)
		this->animationComponent->Play("INTERSECTION", dt);
}

void FireShot::Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPosition)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", lightPosition);
		target.draw(this->shape);
	}
	else
		target.draw(this->shape);
}
