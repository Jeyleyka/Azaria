#pragma once

#include"stdafx.h"

enum ButtonStates { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

namespace GUI
{
	const float p2pX(const float percent, const sf::VideoMode& vm);
	const float p2pY(const float percent, const sf::VideoMode& vm);
	const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier = 55);

	class Button
	{
	private:
		// Variables
		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;
		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;
		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;
		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

		short unsigned buttonState;
		short unsigned id;

	public:
		// Constructor/Destructor
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned characterSize,
			sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
			sf::Color outlineIdleColor = sf::Color::Transparent, sf::Color outlineHoverColor = sf::Color::Transparent, sf::Color outlineActiveColor = sf::Color::Transparent,
			short unsigned id = 0);

		Button(float x, float y, float width, float height, sf::Texture* textureSheet, short unsigned id = 0);
		~Button();

		// Functions
		const bool IsPressed() const;
		const std::string GetText() const;
		const short unsigned& GetId() const;
		void SetText(const std::string text);
		void SetId(const short unsigned id);
		void Update(const sf::Vector2i& mousePosWindow);
		void Render(sf::RenderTarget& target);
	};

	// DROPDOWN LIST ==================================================================
	class DropDownList
	{
	private:
		// Variables
		sf::Font& font;
		sf::Font& specialFont;

		std::vector<GUI::Button*> list;

		GUI::Button* activeElement;

		float keytime;
		float keytimeMax;
		bool showList;

		//void InitFont();

	public:
		// Constructor/Destructor
		DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned nrOfElements, unsigned defaultIndex = 0);
		~DropDownList();

		// Functions
		const unsigned short& GetActiveElementId() const;
		const bool GetKeytime();
		void UpdateKeytime(const float& dt);
		void Update(const sf::Vector2i& mousePosWindow, const float& dt);
		void Render(sf::RenderTarget& target);
	};

	// LAYOUT =================================================================
	class Layout
	{
	private:
		sf::Text text;
		sf::Sprite keySprite;
		sf::Texture keyTexture;

		sf::Sprite keySprite2;
		sf::Texture keyTexture2;
		bool active;

	public:
		Layout();
		Layout(float x, float y, sf::Color innerColor, unsigned characterSize, sf::Font* font, std::string str, sf::VideoMode& vm, float spritePosX = 0.f, std::string path = "", std::string path2 = "");
		~Layout();

		// Functions
		void Update();
		void Render(sf::RenderTarget& target);
	};

	// TEXTURE SELECTOR ===================================================================
	class TextureSelector
	{
	private:
		Button* hideBtn;
		Button* layoutBtn;
		Button* tileBtn;
		Button* enemyBtn;

		Layout* layout;
		Layout* keyC;
		Layout* keyL;
		Layout* keyUp;
		Layout* keyDown;
		Layout* KeyTab;
		Layout* tiles;
		Layout* defTile;
		Layout* damTile;
		Layout* dooTile;
		Layout* enemies;
		Layout* rat;
		Layout* bird;
		Layout* blob;
		Layout* spider;


		sf::RectangleShape background;
		sf::RectangleShape container;
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;

		std::string tileString;
		std::map<std::string, Button*> buttons;
		std::map<std::string, Layout*> layouts;
		std::map<std::string, Layout*> configuration;

		float gridSize;
		float keytime;
		const float keytimeMax;
		bool active;
		bool hidden;
		bool showConfiguration;
		bool showTile;
		bool showEnemy;

	public:
		TextureSelector(float x, float y, float width, float height, float gridSize, const sf::Texture* textureSheet, sf::Font& font,
			std::string text, std::string layText, std::string tileText, std::string enemyText, sf::VideoMode& vm);
		~TextureSelector();

		// Functions
		const bool& GetActive() const;
		const sf::IntRect& GetTextureRect() const;
		const bool GetKeytime();
		void UpdateKeytime(const float& dt);
		void Update(const sf::Vector2i& mousePosWindow, const float& dt);
		void Render(sf::RenderTarget& target);
	};

	// PROGRESSBAR ==========================================================
	class ProgressBar
	{
	private:
		sf::Text text;
		sf::RectangleShape back;
		sf::RectangleShape inner;

		std::string barString;

		float maxWidth;

		int maxValue;

	public:
		ProgressBar(float x, float y, float width, float height, int maxValue, sf::Color innerColor, unsigned characterSize, sf::VideoMode& vm, sf::Font* font = NULL);
		~ProgressBar();

		// Functions
		void Update(const int currentValue);
		void Render(sf::RenderTarget& target);
	};

	enum CardStates { CRD_IDLE = 0, CRD_HOVER, CRD_ACTIVE };

// Card ==========================================================
	class Card
	{
	private:
		// Variables
		sf::Font font;
		sf::RectangleShape bg;
		sf::Sprite item;
		sf::Texture itemTexture;
		sf::Text desc;
		sf::Texture coinTexture;
		sf::Sprite coin;
		sf::Text priceT;
		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;
		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;
		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

		unsigned id;
		int price;

		unsigned short cardState;

		bool cardIsClick;

	public:
		// Constructor/Destructor
		Card(unsigned id, float posX, float posY, float ratio, float itemRatio, const sf::VideoMode& vm, std::string textureFile, sf::Font font, std::string text, int price,
			sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor, sf::Color idleColor, sf::Color hoverColor,
			sf::Color activeColor, sf::Color outlineIdleColor = sf::Color::Transparent, sf::Color outlineHoverColor = sf::Color::Transparent,
			sf::Color outlineActiveColor = sf::Color::Transparent);
		~Card();

		const bool& GetClick() const;
		const int& GetPrice() const;
		const unsigned& GetId() const;
		const unsigned short& GetType() const;

		void Update(const sf::Vector2f& mousePosView);
		void Render(sf::RenderTarget& target);
	};
}

