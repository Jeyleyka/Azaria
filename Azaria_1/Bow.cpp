#include "stdafx.h"
#include "Bow.h"

Bow::Bow(unsigned level, unsigned damageMin, unsigned damageMax, unsigned range, unsigned value, std::string textureFile, std::string arrowTexture)
    : RangedWeapon(level, damageMin, damageMax, range, value, textureFile)
{
    this->arrow = new Arrow(arrowTexture);
    this->weaponTexture.loadFromFile(textureFile);
    this->weaponSprite.setTexture(this->weaponTexture);
    this->weaponSprite.setOrigin(this->weaponSprite.getGlobalBounds().width / 2.f, this->weaponSprite.getGlobalBounds().height);

    this->shootTimer = 20;
}

Bow::~Bow()
{

}

Bow* Bow::Clone()
{
    return new Bow(*this);
}

void Bow::UpdateArrow()
{

}

void Bow::CollisionWithEnemy(Enemy* enemy)
{
    for (size_t i = 0; i < this->arrows.size(); i++)
    {
        if (this->arrows[i].shape.getGlobalBounds().intersects(enemy->GetGlobalBounds()))
            std::cout << "HIT!\n";
    }
}

void Bow::Update(const sf::Vector2f& mousePosView, const sf::Vector2f center, const sf::View& view)
{
    this->aimDir = mousePosView - center;
    this->aimDirNorm = aimDir / sqrtf(pow(aimDir.x, 2) + pow(aimDir.y, 2));

    this->weaponSprite.setPosition(center);

    float dX = mousePosView.x - this->weaponSprite.getPosition().x;
    float dY = mousePosView.y - this->weaponSprite.getPosition().y;

    const float PI = 3.14159265f;
    float deg = atan2(dY, dX) * 180.f / PI;

    this->weaponSprite.setRotation(deg + 90.f);

    if (this->shootTimer < 20)
        this->shootTimer++;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->shootTimer >= 20)
    {
        this->arrow->shape.setPosition(center);
        this->arrow->currentVelocity = this->aimDirNorm * this->arrow->maxSpeed;

        this->arrows.push_back(Arrow(*this->arrow));
        this->shootTimer = 0;
    }

    for (size_t i = 0; i < this->arrows.size(); i++)
    {
        this->arrows[i].shape.setRotation(deg + 90.f);
        this->arrows[i].shape.move(this->arrows[i].currentVelocity);

        if (this->arrows[i].shape.getPosition().x < 0 || this->arrows[i].shape.getPosition().x > 3 * view.getSize().x ||
            this->arrows[i].shape.getPosition().y < 0 || this->arrows[i].shape.getPosition().x > 3 * view.getSize().y)
            this->arrows.erase(this->arrows.begin() + i);
    }

    this->UpdateArrow();
}

void Bow::Render(sf::RenderTarget& target, sf::Shader* shader)
{
    if (shader)
        target.draw(this->weaponSprite, shader);
    else
        target.draw(this->weaponSprite);

    for (size_t i = 0; i < this->arrows.size(); i++)
    {
        target.draw(this->arrows[i].shape);
    }

    //if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    //   target.draw(this->rangeZone);
}
