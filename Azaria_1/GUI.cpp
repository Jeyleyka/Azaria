#include"stdafx.h"
#include "Gui.h"

const float GUI::p2pX(const float percent, const sf::VideoMode& vm)
{
	return std::floor(static_cast<float>(vm.width) * (percent / 100.f));
}

const float GUI::p2pY(const float percent, const sf::VideoMode& vm)
{
	return std::floor(static_cast<float>(vm.height) * (percent / 100.f));
}

const unsigned GUI::calcCharSize(const sf::VideoMode& vm, const unsigned modifier)
{
	return static_cast<unsigned>((vm.width + vm.height) / modifier);
}

GUI::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned characterSize,
	sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
	sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor,
	short unsigned id)
{
	this->buttonState = BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idleColor);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outlineIdleColor);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(textIdleColor);
	this->text.setCharacterSize(characterSize);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + this->shape.getGlobalBounds().height / 4.f
	);

	this->textIdleColor = textIdleColor;
	this->textHoverColor = textHoverColor;
	this->textActiveColor = textActiveColor;

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->outlineIdleColor = outlineIdleColor;
	this->outlineHoverColor = outlineHoverColor;
	this->outlineActiveColor = outlineActiveColor;
}

GUI::Button::Button(float x, float y, float width, float height, sf::Texture* textureSheet, short unsigned id)
{
	this->buttonState = BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setTexture(textureSheet);
}

GUI::Button::~Button()
{
}


// Functions

const bool GUI::Button::IsPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}

const std::string GUI::Button::GetText() const
{
	return this->text.getString();
}

const short unsigned& GUI::Button::GetId() const
{
	return this->id;
}

void GUI::Button::SetText(const std::string text)
{
	this->text.setString(text);
}

void GUI::Button::SetId(const short unsigned id)
{
	this->id = id;
}

void GUI::Button::Update(const sf::Vector2i& mousePosWindow)
{
	this->buttonState = BTN_IDLE;

	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->buttonState = BTN_ACTIVE;
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->shape.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void GUI::Button::Render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

// DROP DOWN LIST ================================================
GUI::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned nrOfElements, unsigned defaultIndex)
	: font(font), specialFont(font), showList(false), keytimeMax(1.f), keytime(0.f)
{
	this->specialFont.loadFromFile("Fonts/font.ttf");

	this->activeElement = new GUI::Button(
		x, y, width, height,
		&this->specialFont, list[defaultIndex], 15,
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50), // 150 30 241 - purple
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50));

	for (unsigned i = 0; i < nrOfElements; i++)
	{
		this->list.push_back(new GUI::Button(
			x, y + ((i + 1) * height), width, height,
			&this->specialFont, list[i], 15,
			sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50), // 150 30 241 - purple
			sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
			sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0), i
		));
	}
}

GUI::DropDownList::~DropDownList()
{
	delete this->activeElement;

	for (size_t i = 0; i < this->list.size(); i++)
	{
		delete this->list[i];
	}
}

// Functions
const unsigned short& GUI::DropDownList::GetActiveElementId() const
{
	return this->activeElement->GetId();
}

const bool GUI::DropDownList::GetKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

void GUI::DropDownList::UpdateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.f * dt;
}

void GUI::DropDownList::Update(const sf::Vector2i& mousePosWindow, const float& dt)
{
	this->UpdateKeytime(dt);
	this->activeElement->Update(mousePosWindow);

	if (this->activeElement->IsPressed() && this->GetKeytime())
	{
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->Update(mousePosWindow);

			if (i->IsPressed() && this->GetKeytime())
			{
				this->showList = false;
				this->activeElement->SetText(i->GetText());
				this->activeElement->SetId(i->GetId());
			}
		}
	}
}

void GUI::DropDownList::Render(sf::RenderTarget& target)
{
	this->activeElement->Render(target);

	if (this->showList)
	{
		for (auto& i : this->list)
			i->Render(target);
	}
}

// LAYOUT =================================================================
GUI::Layout::Layout()
{

}

GUI::Layout::Layout(float x, float y, sf::Color innerColor, unsigned characterSize, sf::Font* font, std::string str, sf::VideoMode& vm, float spritePosX, std::string path, std::string path2)
{
	this->active = false;
	this->text.setString(str);
	this->text.setFont(*font);
	this->text.setPosition(x, y);

	this->keyTexture.loadFromFile(path);
	this->keySprite.setTexture(this->keyTexture);
	this->keySprite.setPosition(spritePosX, this->text.getPosition().y);

	this->keyTexture2.loadFromFile(path2);
	this->keySprite2.setTexture(this->keyTexture2);
	this->keySprite2.setPosition(spritePosX + 80.f, this->text.getPosition().y);
}

GUI::Layout::~Layout()
{
}

void GUI::Layout::Update()
{

}

void GUI::Layout::Render(sf::RenderTarget& target)
{
	target.draw(this->keySprite2);
	target.draw(this->keySprite);
	target.draw(this->text);
}

// TEXTURE SELECTOR ===============================================
GUI::TextureSelector::TextureSelector(float x, float y, float width, float height, float gridSize, const sf::Texture* textureSheet,
	sf::Font& font, std::string text, std::string layText, std::string tileText, std::string enemyText, sf::VideoMode& vm)
	: keytimeMax(1.f), keytime(0.f), active(false), hidden(false)
{
	this->gridSize = gridSize;
	float offset = gridSize;

	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x + offset, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->sheet.setTexture(*textureSheet);
	this->sheet.setPosition(x + offset, y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
		this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->bounds.getGlobalBounds().height)));

	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
		this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->bounds.getGlobalBounds().height)));

	this->selector.setPosition(x + offset, y);
	this->selector.setSize(sf::Vector2f(gridSize, gridSize));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Red);

	this->textureRect.width = static_cast<int>(this->gridSize);
	this->textureRect.height = static_cast<int>(this->gridSize);

	this->background.setSize(sf::Vector2f(static_cast<float>(16), static_cast<float>(vm.height)));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	this->container.setSize(sf::Vector2f(static_cast<float>(vm.width) / 2.f, static_cast<float>(vm.height) / 2.f));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(sf::Vector2f(static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f, static_cast<float>(vm.height) / 2.f - this->container.getSize().y / 2.f));

	//this->configuration["LAYOUT"] = new Layout(this->container.getPosition().x + this->container.getPosition().x / 2.f + 150.f, 270.f, sf::Color(255, 255, 255, 200), 25, &font, "LAYOUT", vm, 0.f, "Resources/Images/Layout/C.png");

	//std::cout << "Max size: " << this->layouts.max_size() << std::endl;

	//this->layouts["Layout"] = new Layout(this->container.getPosition().x + this->container.getPosition().x / 2.f + GUI::p2pX(8.92f, vm), GUI::p2pY(25.7f, vm), sf::Color(255, 255, 255, 200), 25, &font, "LAYOUT", vm);

	//this->layouts["LAYOUT"] = Layout();

	this->layout = new Layout(this->container.getPosition().x + this->container.getPosition().x / 2.f + GUI::p2pX(8.92f, vm), GUI::p2pY(25.7f, vm), sf::Color(255, 255, 255, 200), 25, &font, "LAYOUT", vm);
	this->keyC = new Layout(this->container.getPosition().x + 20.f, GUI::p2pY(30.4f, vm), sf::Color(255, 255, 255, 200), 25, &font, "To create a collision tile press - ", vm, GUI::p2pX(60.1f, vm), "Resources/Images/Layout/C.png");
	this->keyL = new Layout(this->container.getPosition().x + 20.f, 420.f, sf::Color(255, 255, 255, 200), 25, &font, "To add some layers on one tile press - ", vm, GUI::p2pX(65.4f, vm), "Resources/Images/Layout/L.png");
	this->keyUp = new Layout(this->container.getPosition().x + 20.f, 520.f, sf::Color(255, 255, 255, 200), 25, &font, "To increase type of tile press - ", vm, GUI::p2pX(58.9f, vm), "Resources/Images/Layout/Up.png");
	this->keyDown = new Layout(this->container.getPosition().x + 20.f, 620.f, sf::Color(255, 255, 255, 200), 25, &font, "To decrease type of tile press - ", vm, GUI::p2pX(59.5f, vm), "Resources/Images/Layout/Down.png");
	this->KeyTab = new Layout(this->container.getPosition().x + 20.f, 720.f, sf::Color(255, 255, 255, 200), 25, &font, "To add enemy press - ", vm, GUI::p2pX(47.6f, vm), "Resources/Images/Layout/Tab.png");

	this->tiles = new Layout(this->container.getPosition().x + this->container.getPosition().x / 2.f + 150.f, 270.f, sf::Color(255, 255, 255, 200), 25, &font, "TYPES OF TILE", vm);
	this->defTile = new Layout(this->container.getPosition().x + 20.f, 320.f, sf::Color(255, 255, 255, 200), 25, &font, "Example of default tile - ", vm, GUI::p2pX(52.3f, vm), "Resources/Tiles/new_tile2.png", "Resources/Tiles/some.png");
	this->damTile = new Layout(this->container.getPosition().x + 20.f, 420.f, sf::Color(255, 255, 255, 200), 25, &font, "Example of damage tile - ", vm, GUI::p2pX(52.9f, vm), "Resources/Tiles/lava.png", "Resources/Tiles/intrstore.png");
	this->dooTile = new Layout(this->container.getPosition().x + 20.f, 520.f, sf::Color(255, 255, 255, 200), 25, &font, "Example of doodad tile - ", vm, GUI::p2pX(52.9f, vm), "Resources/Tiles/stone.png");

	this->enemies = new Layout(this->container.getPosition().x + this->container.getPosition().x / 2.f + GUI::p2pX(8.92f, vm), GUI::p2pY(25.7f, vm), sf::Color(255, 255, 255, 200), 25, &font, "TYPES OF ENEMIES", vm);
	this->rat = new Layout(this->container.getPosition().x + 20.f, GUI::p2pY(30.4f, vm), sf::Color(255, 255, 255, 200), 25, &font, "First type of enemy is rat - ", vm, GUI::p2pX(53.1f, vm), "Resources/Sprites/Enemy/rat-editor.png");
	this->bird = new Layout(this->container.getPosition().x + 20.f, 420.f, sf::Color(255, 255, 255, 200), 25, &font, "Second type of enemy is bird - ", vm, GUI::p2pX(56.5f, vm), "Resources/Sprites/Enemy/bird-editor.png");
	this->blob = new Layout(this->container.getPosition().x + 20.f, 520.f, sf::Color(255, 255, 255, 200), 25, &font, "Third type of enemy is blob - ", vm, GUI::p2pX(55.3f, vm), "Resources/Sprites/Enemy/blob-editor.png");
	this->spider = new Layout(this->container.getPosition().x + 20.f, 620.f, sf::Color(255, 255, 255, 200), 25, &font, "Fourth type of enemy is spider - ", vm, GUI::p2pX(57.7f, vm), "Resources/Sprites/Enemy/spider-editor.png");

	this->hideBtn = new GUI::Button(
		x, y, 50.f, 50.f,
		&font, text, 20,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50), // 150 30 241 - purple
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50)
	);

	this->layoutBtn = new GUI::Button(
		x, y + 70.f, 50.f, 50.f,
		&font, layText, 14,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50), // 150 30 241 - purple
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50)
	);

	this->tileBtn = new GUI::Button(
		x, y + 140.f, 50.f, 50.f,
		&font, tileText, 19,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50), // 150 30 241 - purple
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50)
	);

	this->enemyBtn = new GUI::Button(
		x, y + 210.f, 50.f, 50.f,
		&font, enemyText, 16,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50), // 150 30 241 - purple
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50)
	);
}

GUI::TextureSelector::~TextureSelector()
{

	delete this->hideBtn;
	delete this->layoutBtn;
	delete this->tileBtn;
	delete this->enemyBtn;
	delete this->layout;
	delete this->keyC;
	delete this->keyL;
	delete this->keyUp;
	delete this->keyDown;
	delete this->KeyTab;

	auto it = this->configuration.begin();
	for (it = this->configuration.begin(); it != this->configuration.end(); it++)
		delete it->second;
}

// Functions
const bool& GUI::TextureSelector::GetActive() const
{
	return this->active;
}

const sf::IntRect& GUI::TextureSelector::GetTextureRect() const
{
	return this->textureRect;
}

const bool GUI::TextureSelector::GetKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

void GUI::TextureSelector::UpdateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.f * dt;
}

void GUI::TextureSelector::Update(const sf::Vector2i& mousePosWindow, const float& dt)
{
	this->UpdateKeytime(dt);
	this->hideBtn->Update(mousePosWindow);
	this->layoutBtn->Update(mousePosWindow);
	this->tileBtn->Update(mousePosWindow);
	this->enemyBtn->Update(mousePosWindow);

	auto it = this->configuration.begin();
	for (it = this->configuration.begin(); it != this->configuration.end(); it++)
		it->second->Update();

	if (this->hideBtn->IsPressed() && this->GetKeytime())
	{
		if (this->hidden)
			this->hidden = false;
		else
			this->hidden = true;
	}

	if (this->layoutBtn->IsPressed() && this->GetKeytime())
	{
		if (this->showConfiguration)
			this->showConfiguration = false;
		else
		{
			this->showTile = false;
			this->showEnemy = false;
			this->showConfiguration = true;
		}
	}

	if (this->tileBtn->IsPressed() && this->GetKeytime())
	{
		if (this->showTile)
			this->showTile = false;
		else
		{
			this->showConfiguration = false;
			this->showEnemy = false;
			this->showTile = true;
		}
	}

	if (this->enemyBtn->IsPressed() && this->GetKeytime())
	{
		if (this->showEnemy)
			this->showEnemy = false;
		else
		{
			this->showConfiguration = false;
			this->showTile = false;
			this->showEnemy = true;
		}
	}

	if (!this->hidden)
	{
		this->active = false;

		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			this->active = true;

			this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
			this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);

			this->selector.setPosition(this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
				this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize);

			this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
			this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
		}
	}
}

void GUI::TextureSelector::Render(sf::RenderTarget& target)
{
	if (!this->hidden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);

		if (this->active)
			target.draw(this->selector);
	}

	if (this->showConfiguration)
	{
		auto it = this->configuration.begin();
		for (it = this->configuration.begin(); it != this->configuration.end(); it++)
			it->second->Render(target);
	}

	if (this->showConfiguration)
	{
		target.draw(this->background);
		target.draw(this->container);
		this->layout->Render(target);
		this->keyC->Render(target);
		this->keyL->Render(target);
		this->keyUp->Render(target);
		this->keyDown->Render(target);
		this->KeyTab->Render(target);
	}

	if (this->showTile)
	{
		target.draw(this->background);
		target.draw(this->container);
		this->tiles->Render(target);
		this->defTile->Render(target);
		this->damTile->Render(target);
		this->dooTile->Render(target);

	}

	if (this->showEnemy)
	{
		target.draw(this->background);
		target.draw(this->container);
		this->enemies->Render(target);
		this->rat->Render(target);
		this->bird->Render(target);
		this->blob->Render(target);
		this->spider->Render(target);

	}

	this->hideBtn->Render(target);
	this->layoutBtn->Render(target);
	this->tileBtn->Render(target);
	this->enemyBtn->Render(target);
}

// PROGRESSBAR ===============================================
GUI::ProgressBar::ProgressBar(float _x, float _y, float _width, float _height, int maxValue, sf::Color innerColor, unsigned characterSize, sf::VideoMode& vm, sf::Font* font)
{
	float width = GUI::p2pX(_width, vm);
	float height = GUI::p2pY(_height, vm);
	float x = GUI::p2pX(_x, vm);
	float y = GUI::p2pY(_y, vm);

	this->maxWidth = width;
	this->maxValue = maxValue;

	this->back.setSize(sf::Vector2f(width, height));
	this->back.setFillColor(sf::Color(50, 50, 50, 200));
	this->back.setPosition(x, y);

	this->inner.setSize(sf::Vector2f(width, height));
	this->inner.setFillColor(innerColor);
	this->inner.setPosition(this->back.getPosition());

	if (font)
	{
		this->text.setFont(*font);
		this->text.setCharacterSize(GUI::calcCharSize(vm, characterSize));
		this->text.setPosition(this->inner.getPosition().x + GUI::p2pX(0.59f, vm), this->inner.getPosition().y - GUI::p2pY(0.28f, vm));
	}
}

GUI::ProgressBar::~ProgressBar()
{
}

// Functions
void GUI::ProgressBar::Update(const int currentValue)
{
	float percent = static_cast<float>(currentValue) / static_cast<float>(maxValue);

	this->inner.setSize(sf::Vector2f(static_cast<float>(std::floor(this->maxWidth * percent)), this->inner.getSize().y));

	this->barString = std::to_string(currentValue) + "/" + std::to_string(maxValue);
	this->text.setString(this->barString);
}

void GUI::ProgressBar::Render(sf::RenderTarget& target)
{
	target.draw(this->back);
	target.draw(this->inner);
	target.draw(this->text);
}

// CARD ===============================================
GUI::Card::Card(unsigned id, float posX, float posY, float ratio, float itemRatio, const sf::VideoMode& vm, std::string textureFile,
	sf::Font font, std::string text, int price,
	sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
	sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor)
{
	this->cardState = CardStates::CRD_IDLE;

	this->cardIsClick = false;

	this->price = price;
	this->id = id;

	this->bg.setFillColor(idleColor);
	this->bg.setOutlineColor(sf::Color::White);
	this->bg.setOutlineThickness(1.f);
	this->bg.setSize(sf::Vector2f(150.f, 230.f));
	this->bg.setPosition(posX, posY);

	this->priceT.setFont(this->font);
	this->priceT.setCharacterSize(32);
	this->priceT.setString(std::to_string(this->price));
	this->priceT.setPosition(this->bg.getPosition().x + this->bg.getSize().x / 2.f - 30.f, this->bg.getPosition().y + 20.f);
	this->priceT.setFillColor(textIdleColor);

	if (!this->coinTexture.loadFromFile("Resources/Sprites/Coin/coin-shop.png")) exit(3);

	this->coin.setTexture(this->coinTexture);
	this->coin.setPosition(this->priceT.getPosition().x + 35.f, this->bg.getPosition().y + 25.f);

	if (!this->itemTexture.loadFromFile(textureFile)) exit(5);
	this->item.setTexture(this->itemTexture);
	this->item.setPosition(this->bg.getPosition().x + this->bg.getSize().x / 2.f - 10.f + itemRatio, this->bg.getPosition().y + this->bg.getSize().y / 2.f - 30.f);

	this->font.loadFromFile("Fonts/font3.ttf");

	this->desc.setCharacterSize(24);
	this->desc.setFont(this->font);
	this->desc.setString(text);
	this->desc.setPosition(this->item.getPosition().x - 55.f + ratio, this->item.getPosition().y + 100.f);
	this->desc.setFillColor(textIdleColor);

	this->textIdleColor = textIdleColor;
	this->textHoverColor = textHoverColor;
	this->textActiveColor = textActiveColor;

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->outlineIdleColor = outlineIdleColor;
	this->outlineHoverColor = outlineHoverColor;
	this->outlineActiveColor = outlineActiveColor;
}

GUI::Card::~Card()
{

}

const bool& GUI::Card::GetClick() const
{
	return this->cardIsClick;
}

const int& GUI::Card::GetPrice() const
{
	return this->price;
}

const unsigned& GUI::Card::GetId() const
{
	return this->id;
}

const unsigned short& GUI::Card::GetType() const
{
	return this->cardState;
}

void GUI::Card::Update(const sf::Vector2f& mousePosView)
{
	this->cardState = CardStates::CRD_IDLE;

	if (this->bg.getGlobalBounds().contains(mousePosView))
	{
		this->cardState = CRD_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->cardState = CRD_ACTIVE;
			this->cardIsClick = true;
		}
	}

	switch (this->cardState)
	{
	case CRD_IDLE:
		this->bg.setFillColor(this->idleColor);
		this->priceT.setFillColor(this->textIdleColor);
		this->desc.setFillColor(this->textIdleColor);
		//this->bg.setOutlineColor(this->outlineIdleColor);
		break;

	case CRD_HOVER:
		this->bg.setFillColor(this->hoverColor);
		this->priceT.setFillColor(this->textHoverColor);
		this->desc.setFillColor(this->textHoverColor);
		//this->bg.setOutlineColor(this->outlineHoverColor);
		break;

	case CRD_ACTIVE:
		this->bg.setFillColor(this->activeColor);
		this->priceT.setFillColor(this->textActiveColor);
		this->desc.setFillColor(this->textActiveColor);
		//this->bg.setOutlineColor(this->outlineActiveColor);
		break;

	default:
		this->bg.setFillColor(sf::Color::Red);
		this->priceT.setFillColor(sf::Color::Blue);
		this->desc.setFillColor(sf::Color::Blue);
		this->bg.setOutlineColor(sf::Color::Green);
		break;
	}
}

void GUI::Card::Render(sf::RenderTarget& target)
{
	target.draw(this->bg);
	target.draw(this->priceT);
	target.draw(this->coin);
	target.draw(this->item);
	target.draw(this->desc);
}
