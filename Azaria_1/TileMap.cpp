#include "stdafx.h"
#include "TileMap.h"

void TileMap::SetNumberDiedEnemies()
{
	this->numberDiedEnemies++;
	//std::cout << "Enemies died: " << this->numberDiedEnemies << "\n";
}

void TileMap::Clear()
{
	if (!this->map.empty())
	{
		for (int x = 0; x < this->map.size(); x++)
		{
			for (int y = 0; y < this->map[x].size(); y++)
			{
				for (int z = 0; z < this->map[x][y].size(); z++)
				{
					for (size_t k = 0; k < this->map[x][y][z].size(); k++)
					{
						delete this->map[x][y][z][k];
						this->map[x][y][z][k] = NULL;
					}
					this->map[x][y][z].clear();
				}
				this->map[x][y].clear();
			}
			this->map[x].clear();
		}
		this->map.clear();
	}
	//std::cout << this->map.size() << "\n";
}

TileMap::TileMap(float gridSize, int width, int height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeI = static_cast<int>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	this->layers = 1;
	this->textureFile = texture_file;

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector< std::vector<Tile*> > >());
	for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector< std::vector<Tile*> >());

			for (int z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, std::vector<Tile*>());
			}
		}
	}

	if (!this->tileSheet.loadFromFile(texture_file))
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file << "\n";

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
}

TileMap::TileMap(const std::string file_name)
{
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->LoadFromFile(file_name);

	this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
	this->Clear();
}

const bool TileMap::TileEmpty(const int x, const int y, const int z) const
{
	if (x >= 0 && x < this->maxSizeWorldGrid.x &&
		y >= 0 && y < this->maxSizeWorldGrid.y &&
		z >= 0 && z < this->layers)

	{
		return this->map[x][y][z].empty();
	}

	return false;
}

const int& TileMap::GetNumberDiedEnemies() const
{
	return this->numberDiedEnemies;
}

//Accessors
const sf::Texture* TileMap::GetTileSheet() const
{
	return &this->tileSheet;
}

const int TileMap::GetLayerSize(const int x, const int y, const int layer) const
{
	if (x >= 0 && x < static_cast<int>(this->map.size()))
	{
		if (y >= 0 && y < static_cast<int>(this->map[x].size()))
		{
			if (layer >= 0 && layer < static_cast<int>(this->map[x][y].size()))
			{
				return this->map[x][y][layer].size();
			}
		}
	}

	return -1;
}

const sf::Vector2i& TileMap::GetMaxSizeGrid() const
{
	return this->maxSizeWorldGrid;
}

const sf::Vector2f& TileMap::GetMaxSizeF() const
{
	return this->maxSizeWorldF;
}

//Functions
void TileMap::AddTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool& collision, const short& type)
{
	/* Take three indicies from the mouse position in the grid and add a tile to that position if the internal tilemap array allows it. */

	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		/* OK To add tile. */
		this->map[x][y][z].push_back(new RegularTile(type, x, y, this->gridSizeF, this->tileSheet, texture_rect, collision));

		//std::cout << "DEGBUG: ADDED TILE!" << "\n";	
	}
}

void TileMap::AddTile(const int x, const int y, const int z, const sf::IntRect& texture_rect,
	const int enemy_type, const int enemy_amount, const int enemy_tts, float enemy_md)
{
	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		this->map[x][y][z].push_back(new EnemySpawnerTile(x, y, this->gridSizeF, this->tileSheet, texture_rect,
			enemy_type, enemy_amount, enemy_tts, 15000.f));
	}
}

void TileMap::RemoveTile(const int x, const int y, const int z, const short type)
{
	/* Take three indicies from the mouse position in the grid and remove a tile at that position if the internal tilemap array allows it. */

	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (!this->map[x][y][z].empty())
		{
			/* OK To remove tile. */
			if (type >= 0)
			{
				if (this->map[x][y][z].back()->GetType() == type)
				{
					delete this->map[x][y][z][this->map[x][y][z].size() - 1];
					this->map[x][y][z].pop_back();
					//std::cout << "DEGBUG: REMOVED TILE!" << "\n";
				}
			}
			else
			{
				delete this->map[x][y][z][this->map[x][y][z].size() - 1];
				this->map[x][y][z].pop_back();
				//std::cout << "DEGBUG: REMOVED TILE!" << "\n";
			}
		}
	}
}

void TileMap::SaveToFile(const std::string file_name)
{
	/*Saves the entire tilemap to a text-file.
	Format:
	Basic:
	Size x y
	gridSize
	layers
	texture file

	All tiles:
	type
	gridPos x y layer
	Texture rect x y
	collision
	tile_specific...
	*/

	std::ofstream out_file;

	out_file.open(file_name);

	if (out_file.is_open())
	{
		out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
			<< this->gridSizeI << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";

		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					if (!this->map[x][y][z].empty())
					{
						for (size_t k = 0; k < this->map[x][y][z].size(); k++)
						{
							out_file << x << " " << y << " " << z << " " <<
								this->map[x][y][z][k]->GetAsString()
								<< " ";
						}
					}
				}
			}
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILENAME: " << file_name << "\n";
	}

	out_file.close();
}

void TileMap::LoadFromFile(const std::string file_name)
{
	std::ifstream in_file;

	in_file.open(file_name);

	if (in_file.is_open())
	{
		sf::Vector2i size;
		int gridSize = 0;
		int layers = 0;
		std::string texture_file = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0;
		int trY = 0;
		bool collision = false;
		short type = 0;

		//Basics
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		//Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = gridSize;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->maxSizeWorldF.x = static_cast<float>(size.x * gridSize);
		this->maxSizeWorldF.y = static_cast<float>(size.y * gridSize);
		this->layers = layers;
		this->textureFile = texture_file;

		this->Clear();

		this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector< std::vector<Tile*> > >());
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector< std::vector<Tile*> >());

				for (int z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, std::vector<Tile*>());
				}
			}
		}

		if (!this->tileSheet.loadFromFile(texture_file))
			std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file << "\n";

		//Load all tiles
		while (in_file >> x >> y >> z >> type)
		{
			std::cout << type << "\n";
			if (type == TileTypes::ENEMYSPAWNER)
			{
				//amount, time, max dist
				int enemy_type = 0;
				int	enemy_am = 0;
				int	enemy_tts = 0;
				int	enemy_md = 0;

				in_file >> trX >> trY >> enemy_type >> enemy_am >> enemy_tts >> enemy_md;

				this->map[x][y][z].push_back(
					new EnemySpawnerTile(
						x, y,
						this->gridSizeF,
						this->tileSheet,
						sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
						enemy_type,
						enemy_am,
						enemy_tts,
						enemy_md
					)
				);
			}
			else
			{
				in_file >> trX >> trY >> collision;

				this->map[x][y][z].push_back(
					new RegularTile(
						type,
						x, y,
						this->gridSizeF,
						this->tileSheet,
						sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
						collision
					)
				);
			}
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << "\n";
	}

	in_file.close();
}

const bool TileMap::CheckType(const int x, const int y, const int z, const short type) const
{
	return this->map[x][y][this->layer].back()->GetType() == type;
}

void TileMap::UpdateWorldBoundsCollision(Entity* entity, const float& dt)
{
	//WORLD BOUNDS
	if (entity->GetPosition().x < 0.f)
	{
		entity->SetPosition(0.f, entity->GetPosition().y);
		entity->StopVelocityX();
	}
	else if (entity->GetPosition().x + entity->GetGlobalBounds().width > this->maxSizeWorldF.x)
	{
		entity->SetPosition(this->maxSizeWorldF.x - entity->GetGlobalBounds().width, entity->GetPosition().y);
		entity->StopVelocityX();
	}
	if (entity->GetPosition().y < 0.f)
	{
		entity->SetPosition(entity->GetPosition().x, 0.f);
		entity->StopVelocityY();
	}
	else if (entity->GetPosition().y + entity->GetGlobalBounds().height > this->maxSizeWorldF.y)
	{
		entity->SetPosition(entity->GetPosition().x, this->maxSizeWorldF.y - entity->GetGlobalBounds().height);
		entity->StopVelocityY();
	}
}

void TileMap::UpdateTileCollision(Entity* entity, const float& dt)
{
	//TILES
	this->layer = 0;

	this->fromX = entity->GetGridPosition(this->gridSizeI).x - 1;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = entity->GetGridPosition(this->gridSizeI).x + 3;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = entity->GetGridPosition(this->gridSizeI).y - 1;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = entity->GetGridPosition(this->gridSizeI).y + 3;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				sf::FloatRect playerBounds = entity->GetGlobalBounds();
				sf::FloatRect wallBounds = this->map[x][y][this->layer][k]->GetGlobalBounds();
				sf::FloatRect nextPositionBounds = entity->GetNextPositionBounds(dt);

				if (this->map[x][y][this->layer][k]->GetCollision() &&
					this->map[x][y][this->layer][k]->Intersects(nextPositionBounds)
					)
				{
					//Bottom collision
					if (playerBounds.top < wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->StopVelocityY();
						entity->SetPosition(playerBounds.left, wallBounds.top - playerBounds.height);
					}

					//Top collision
					else if (playerBounds.top > wallBounds.top
						&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						entity->StopVelocityY();
						entity->SetPosition(playerBounds.left, wallBounds.top + wallBounds.height);
					}

					//Right collision
					if (playerBounds.left < wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						entity->StopVelocityX();
						entity->SetPosition(wallBounds.left - playerBounds.width, playerBounds.top);
					}

					//Left collision
					else if (playerBounds.left > wallBounds.left
						&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						entity->StopVelocityX();
						entity->SetPosition(wallBounds.left + wallBounds.width, playerBounds.top);
					}
				}
			}
		}
	}
}

void TileMap::UpdateTiles(Entity* entity, const float& dt, EnemySystem& enemySystem)
{
	//TILES
	this->layer = 0;

	this->fromX = entity->GetGridPosition(this->gridSizeI).x - 15;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = entity->GetGridPosition(this->gridSizeI).x + 16;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = entity->GetGridPosition(this->gridSizeI).y - 8;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = entity->GetGridPosition(this->gridSizeI).y + 9;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				//Update the tile
				this->map[x][y][this->layer][k]->Update();

				//Update tile types (specific)
				if (this->map[x][y][this->layer][k]->GetType() == TileTypes::ENEMYSPAWNER)
				{
					EnemySpawnerTile* es = dynamic_cast<EnemySpawnerTile*>(this->map[x][y][this->layer][k]);
					if (es)
					{
						if (es->GetSpawnTimer() && es->GetEnemyCounter() < es->GetEnemyAmount() && this->numberDiedEnemies <= 1)
						{
							enemySystem.CreateEnemy(es->GetEnemyType(), x * this->gridSizeF, y * this->gridSizeF, *es);
						}
					}
				}
			}
		}
	}
}

void TileMap::Update(Entity* entity, const float& dt)
{

}

void TileMap::Render
(
	sf::RenderTarget& target,
	const sf::Vector2i& gridPosition,
	sf::Shader* shader,
	const sf::Vector2f playerPosition,
	const bool show_collision
)
{
	this->layer = 0;

	this->fromX = gridPosition.x - 15;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = gridPosition.x + 16;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = gridPosition.y - 8;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = gridPosition.y + 9;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				if (this->map[x][y][this->layer][k]->GetType() == TileTypes::DOODAD)
				{
					this->defferedRenderStack.push(this->map[x][y][this->layer][k]);
				}
				else
				{
					if (shader)
						this->map[x][y][this->layer][k]->Render(target, shader, playerPosition);
					else
						this->map[x][y][this->layer][k]->Render(target);
				}

				if (show_collision)
				{
					if (this->map[x][y][this->layer][k]->GetCollision())
					{
						this->collisionBox.setPosition(this->map[x][y][this->layer][k]->GetPosition());
						target.draw(this->collisionBox);
					}

					if (this->map[x][y][this->layer][k]->GetType() == TileTypes::ENEMYSPAWNER)
					{
						this->collisionBox.setPosition(this->map[x][y][this->layer][k]->GetPosition());
						target.draw(this->collisionBox);
					}
				}
			}
		}
	}
}

void TileMap::DefferedRender(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPosition)
{
	while (!this->defferedRenderStack.empty())
	{
		if (shader)
			defferedRenderStack.top()->Render(target, shader, playerPosition);
		else
			defferedRenderStack.top()->Render(target);

		defferedRenderStack.pop();
	}
}