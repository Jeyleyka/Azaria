#pragma once

#include"Tile.h"

class RegularTile : public Tile
{
private:

protected:

public:
	// Constructor/Destructor
	RegularTile(short type, int x, int y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& textureRect, bool collision = false);
	virtual ~RegularTile();

	// Functions
	virtual const std::string GetAsString() const;

	virtual void Update();
	virtual void Render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f playerPosition = sf::Vector2f());
};

