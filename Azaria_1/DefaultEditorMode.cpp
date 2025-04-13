#include "stdafx.h"
#include "DefaultEditorMode.h"

void DefaultEditorMode::InitVariables()
{
    this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
    this->collision = false;
    this->type = DEFAULT;
    this->layer = 0;
    this->tileAddLock = true;
}

void DefaultEditorMode::InitGui()
{
    this->cursorText.setFont(*this->editorStateData->font);
    this->cursorText.setFillColor(sf::Color::White);
    this->cursorText.setCharacterSize(12);
    this->cursorText.setPosition(this->editorStateData->mousePosView->x, this->editorStateData->mousePosView->y);

    this->sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(this->stateData->gfxSettings->resolution.height)));
    this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
    this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
    this->sidebar.setOutlineThickness(1.f);

    this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
    this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::Green);
    this->selectorRect.setTexture(this->tileMap->GetTileSheet());
    this->selectorRect.setTextureRect(this->textureRect);

    this->textureSelector = new GUI::TextureSelector(20.f, 20.f, 320.f, 320.f, this->stateData->gridSize, this->tileMap->GetTileSheet(),
        *this->editorStateData->font, "TS", "Layout", "Tile", "Enemy", this->stateData->gfxSettings->resolution);
}

DefaultEditorMode::DefaultEditorMode(StateData* stateData, TileMap* tileMap, EditorStateData* editorStateData)
    : EditorMode(stateData, tileMap, editorStateData)
{
    this->InitVariables();
    this->InitGui();
}

DefaultEditorMode::~DefaultEditorMode()
{
    delete this->textureSelector;
    delete this->layout;
}

// Functions
void DefaultEditorMode::UpdateInput(const float& dt)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->GetKeytime())
    {
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
        {
            if (!this->textureSelector->GetActive())
            {
                if (this->tileAddLock)
                {
                    if (this->tileMap->TileEmpty(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0))
                    {
                        this->tileMap->AddTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0,
                            this->textureRect, this->collision, this->type);
                    }
                }
                else
                    this->tileMap->AddTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect,
                        this->collision, this->type);
            }
            else
                this->textureRect = this->textureSelector->GetTextureRect();
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->GetKeytime())
    {
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData->mousePosWindow)))
        {
            if (!this->textureSelector->GetActive())
                this->tileMap->RemoveTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("COLLISION"))) && this->GetKeytime())
    {
        if (this->collision)
            this->collision = false;
        else
            this->collision = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("INCREASE_TYPE"))) && this->GetKeytime())
    {
        if (this->type < 2)
            this->type++;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("DECREASE_TYPE"))) && this->GetKeytime())
    {
        if (this->type > 0)
            this->type--;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->editorStateData->keybinds->at("TILE_LOCK"))) && this->GetKeytime())
    {
        if (this->tileAddLock)
            this->tileAddLock = false;
        else
            this->tileAddLock = true;
    }
}

void DefaultEditorMode::UpdateGui(const float& dt)
{
    this->textureSelector->Update(*this->editorStateData->mousePosWindow, dt);

    if (!this->textureSelector->GetActive())
    {
        this->selectorRect.setTextureRect(this->textureRect);
        this->selectorRect.setPosition(this->editorStateData->mousePosGrid->x * this->stateData->gridSize,
            this->editorStateData->mousePosGrid->y * this->stateData->gridSize);
    }

    this->cursorText.setPosition(this->editorStateData->mousePosView->x + 100.f, this->editorStateData->mousePosView->y - 50.f);

    std::stringstream ss;
    ss << "\n" << this->editorStateData->mousePosView->x << " " << this->editorStateData->mousePosView->y <<
        "\n" << this->textureRect.left << " " << this->textureRect.top <<
        "\n" << "Collision: " << this->collision <<
        "\n" << "Type: " << this->type <<
        "\n" << "Tiles: " << this->tileMap->GetLayerSize(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y,
            this->layer) <<
        "\n" << "Tile lock: " << this->tileAddLock;

    this->cursorText.setString(ss.str());
}

void DefaultEditorMode::Update(const float& dt)
{
    this->UpdateInput(dt);
    this->UpdateGui(dt);
}

void DefaultEditorMode::RenderGui(sf::RenderTarget& target)
{
    if (!this->textureSelector->GetActive())
    {
        target.setView(*this->editorStateData->view);
        target.draw(this->selectorRect);
    }

    target.setView(this->stateData->window->getDefaultView());
    this->textureSelector->Render(target);
    target.draw(this->sidebar);

    target.setView(*this->editorStateData->view);
    target.draw(this->cursorText);
}

void DefaultEditorMode::Render(sf::RenderTarget& target)
{
    this->RenderGui(target);
}
