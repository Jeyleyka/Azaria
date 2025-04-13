#include"stdafx.h"
#include "Shop.h"

Shop::Shop(unsigned width, unsigned height, int level, const sf::VideoMode& vm)
{
	this->shopBg.setSize(sf::Vector2f(460.f, 520.f));
	this->shopBg.setPosition(width / 2 - this->shopBg.getSize().x + 50.f,
		height / 2.f - this->shopBg.getSize().y / 2.f - 75.f);
	this->shopBg.setFillColor(sf::Color(74, 70, 58, 240));

	this->font.loadFromFile("Fonts/font3.ttf");

	this->shop.setFont(this->font);
	this->shop.setCharacterSize(36);
	this->shop.setPosition(this->shopBg.getPosition().x + this->shopBg.getSize().x / 2 - 40.f, this->shopBg.getPosition().y);
	this->shop.setString("Shop");

	this->cards.push_back(new GUI::Card(1, this->shopBg.getPosition().x + 5.f, this->shop.getPosition().y + 50.f, 0.f, 0.f, vm,
		"Resources/Sprites/Player/sword_1.png", this->font, "New sword", 25, sf::Color(212, 153, 2, 255), sf::Color(250, 250, 250, 250),
		sf::Color(20, 20, 20, 50), sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));
	this->cards.push_back(new GUI::Card(2, this->shopBg.getPosition().x + 5.f, this->shop.getPosition().y + 280.f, 18.f, -25.f, vm,
		"Resources/Sprites/Player/bow_0.png", this->font, "New weapon", 15, sf::Color(212, 153, 2, 255), sf::Color(250, 250, 250, 250),
		sf::Color(20, 20, 20, 50), sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));

	this->cards.push_back(new GUI::Card(3, this->shopBg.getPosition().x + 155.f, this->shop.getPosition().y + 50.f, 11.f, -15.f, vm,
		"Resources/Sprites/Player/flame.png", this->font, "combustion", 20, sf::Color(212, 153, 2, 255), sf::Color(250, 250, 250, 250),
		sf::Color(20, 20, 20, 50), sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));
	this->cards.push_back(new GUI::Card(4, this->shopBg.getPosition().x + 155.f, this->shop.getPosition().y + 280.f, 19.f, -7.f, vm,
		"Resources/Sprites/Player/ice.png", this->font, "freezing", 15, sf::Color(212, 153, 2, 255), sf::Color(250, 250, 250, 250),
		sf::Color(20, 20, 20, 50), sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));

	this->cards.push_back(new GUI::Card(5, this->shopBg.getPosition().x + 305.f, this->shop.getPosition().y + 50.f, 0.f, 0.f, vm,
		"Resources/Sprites/Player/sword_1.png", this->font, "New sword", 20, sf::Color(212, 153, 2, 255), sf::Color(250, 250, 250, 250),
		sf::Color(20, 20, 20, 50), sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));
	this->cards.push_back(new GUI::Card(6, this->shopBg.getPosition().x + 305.f, this->shop.getPosition().y + 280.f, 0.f, 0.f, vm,
		"Resources/Sprites/Player/sword_1.png", this->font, "New sword", 25, sf::Color(212, 153, 2, 255), sf::Color(250, 250, 250, 250),
		sf::Color(20, 20, 20, 50), sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));
}

Shop::~Shop()
{
	for (auto* i : this->cards)
		delete i;
}

const std::vector<GUI::Card*> Shop::GetArrayCards() const
{
	return this->cards;
}

const sf::Vector2f& Shop::GetCenter() const
{
	return this->shopBg.getPosition() + sf::Vector2f(this->shopBg.getGlobalBounds().width / 2.f, this->shopBg.getGlobalBounds().height / 2.f);
}

void Shop::Update(const sf::Vector2f& mousePosView)
{
	for (auto* i : this->cards)
		i->Update(mousePosView);
}

void Shop::Render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f lightPosition)
{
	target.draw(this->shopBg);
	target.draw(this->shop);

	for (auto* i : this->cards)
		i->Render(target);
}
