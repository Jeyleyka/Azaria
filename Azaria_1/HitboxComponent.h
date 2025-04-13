#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;

	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite& sprite,
		float offset_x, float offset_y,
		float width, float height);
	virtual ~HitboxComponent();

	//Accessors
	const sf::Vector2f& GetPosition() const;
	const sf::FloatRect GetGlobalBounds() const;
	const sf::FloatRect& GetNextPosition(const sf::Vector2f& velocity);

	//Modifiers
	void SetPosition(const sf::Vector2f& position);
	void SetPosition(const float x, const float y);

	//Functions
	bool Intersects(const sf::FloatRect& frect);

	void Update();
	void Render(sf::RenderTarget& target);
};

#endif