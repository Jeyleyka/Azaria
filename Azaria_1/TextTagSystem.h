#pragma once

enum TagTypes { DEFAULT_TAG, MISS_TAG, CRIT_TAG, NEGATIVE_TAG, POSITIVE_TAG, EXPEREINCE_TAG, ENVIRONMENTAL_TAG };

class TextTagSystem
{
private:
	class TextTag
	{
	private:
		sf::Text text;
		sf::Vector2f velocity;

		float dirX;
		float dirY;
		float lifeTime;
		float speed;
		float acceleration;

		int fadeValue;

		bool reverse;

	public:
		TextTag(sf::Font& font, std::string text, float posX, float posY, float dirX, float dirY, sf::Color color, unsigned charSize,
			float lifeTime, bool reverse, float speed, float acceleration, int fadeValue)
		{
			this->text.setFont(font);
			this->text.setPosition(posX, posY);
			this->text.setFillColor(color);
			this->text.setCharacterSize(charSize);
			this->text.setString(text);
			this->dirX = dirX;
			this->dirY = dirY;
			this->lifeTime = lifeTime;
			this->speed = speed;
			this->acceleration = acceleration;
			this->fadeValue = fadeValue;
			this->reverse = reverse;

			if (this->reverse)
			{
				this->velocity.x = this->dirX * this->speed;
				this->velocity.y = this->dirY * this->speed;
			}
		}

		TextTag(TextTag* tag, float posX, float posY, std::string str)
		{
			this->text = tag->text;
			this->text.setString(str);
			this->text.setPosition(posX, posY);
			this->dirX = tag->dirX;
			this->dirY = tag->dirY;
			this->lifeTime = tag->lifeTime;
			this->speed = tag->speed;
			this->acceleration = tag->acceleration;
			this->fadeValue = tag->fadeValue;
			this->reverse = tag->reverse;
			this->velocity = tag->velocity;
		}

		~TextTag()
		{

		}

		// Functions
		inline const bool IsExpired() const { return this->lifeTime <= 0.f; }

		void Update(const float& dt)
		{
			if (this->lifeTime > 0.f)
			{
				this->lifeTime -= 100.f * dt;

				if (this->acceleration > 0.f)
				{
					if (this->reverse)
					{
						this->velocity.x -= this->dirX * this->acceleration * dt;
						this->velocity.y -= this->dirY * this->acceleration * dt;

						if (abs(this->velocity.x) < 0.f)
							this->velocity.x = 0.f;

						if (abs(this->velocity.y) < 0.f)
							this->velocity.y = 0.f;

						this->text.move(this->velocity * dt);
					}
					else
					{
						this->velocity.x += this->dirX * this->acceleration * dt;
						this->velocity.y += this->dirY * this->acceleration * dt;

						if (abs(this->velocity.x) > this->speed)
							this->velocity.x = this->dirX * this->speed;

						if (abs(this->velocity.y) > this->speed)
							this->velocity.y = this->dirX * this->speed;

						this->text.move(this->velocity * dt);
					}
				}
				else
					this->text.move(this->dirX * this->speed * dt, this->dirY * this->speed * dt);
			}

			if (this->fadeValue > 0 && this->text.getFillColor().a >= this->fadeValue)
			{
				this->text.setFillColor(sf::Color(this->text.getFillColor().r, this->text.getFillColor().g, this->text.getFillColor().b,
					this->text.getFillColor().a - this->fadeValue));
			}

		}
		void Render(sf::RenderTarget& target)
		{
			target.draw(this->text);
		}
	};

	sf::Font font;
	std::map<unsigned, TextTag*> tagTemplates;
	std::vector<TextTag*> tags;

	// Initialize functions
	void InitVariables();
	void InitFonts(std::string fontFile);
	void InitTagTemplates();

public:
	// Constructor/Destructor
	TextTagSystem(std::string fontFile);
	virtual ~TextTagSystem();

	// Functions
	void AddTextTag(const unsigned tagTypes, float posX, float posY, const std::string str, const std::string prefix = "", const std::string postfix = "");
	void AddTextTag(const unsigned tagTypes, float posX, float posY, const int i, const std::string prefix = "", const std::string postfix = "");
	void AddTextTag(const unsigned tagTypes, float posX, float posY, const float f, const std::string prefix = "", const std::string postfix = "");
	void Update(const float& dt);
	void Render(sf::RenderTarget& target);
};

