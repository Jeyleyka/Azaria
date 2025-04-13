#include"stdafx.h"
#include "EditorState.h"

// Initializer functions
void EditorState::InitVariables()
{
    this->cameraSpeed = 200.f;
}

void EditorState::InitEditorStateData()
{
    this->editorStateData.view = &this->view;
    this->editorStateData.font = &this->font;
    this->editorStateData.keytime = &this->keytime;
    this->editorStateData.keytimeMax = &this->keytimeMax;
    this->editorStateData.keybinds = &this->keybinds;
    this->editorStateData.mousePosGrid = &this->mousePosGrid;
    this->editorStateData.mousePosScreen = &this->mousePosScreen;
    this->editorStateData.mousePosView = &this->mousePosView;
    this->editorStateData.mousePosWindow = &this->mousePosWindow;
}

void EditorState::InitView()
{
    this->view.setSize(sf::Vector2f(static_cast<float>(this->stateData->gfxSettings->resolution.width), static_cast<float>(this->stateData->gfxSettings->resolution.height)));
    this->view.setCenter(static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f, static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f);
}

void EditorState::InitFonts()
{
    if (!this->font.loadFromFile("Fonts/font3.ttf")) exit(3);
}

void EditorState::InitKeybinds()
{
    std::ifstream ifs("Config/editorstate_key.txt");

    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";

        while (ifs >> key >> key2)
        {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void EditorState::InitPauseMenu()
{
    const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

    this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

    this->pmenu->AddButton("EXIT_STATE", GUI::p2pY(76.1f, vm), GUI::p2pX(14.8f, vm), GUI::p2pY(6.1f, vm), GUI::calcCharSize(vm), "Quit");
    this->pmenu->AddButton("SAVE", GUI::p2pY(19.f, vm), GUI::p2pX(14.8f, vm), GUI::p2pY(6.1f, vm), GUI::calcCharSize(vm), "Save");
    this->pmenu->AddButton("LOAD", GUI::p2pY(28.5f, vm), GUI::p2pX(14.8f, vm), GUI::p2pY(6.1f, vm), GUI::calcCharSize(vm), "Load");
}

void EditorState::InitLayoutMap()
{
    this->layoutMap[0] = "LAYOUT";
}

void EditorState::InitButtons()
{
    //const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

    //this->buttons["LAYOUT"] = new GUI::Button(
    //   GUI::p2pX(1.1f, vm), GUI::p2pY(1.9f, vm), GUI::p2pX(23.8f, vm), GUI::p2pY(20.9f, vm),
    //   &this->font, "Layout", GUI::calcCharSize(vm, 150),
    //   sf::Color(255, 255, 255, 200), sf::Color(200, 200, 200, 150), sf::Color(20, 20, 20, 50), // 150 30 241 - purple
    //   sf::Color(50, 50, 50, 100), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
    //);

    //this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
    //this->bounds.setOutlineThickness(1.f);
    //this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));
    //20.f, 20.f, 320.f, 320.f
}

void EditorState::InitGui()
{

}

void EditorState::InitTileMap()
{
    this->tileMap = new TileMap(this->stateData->gridSize, 33, 21, "Resources/Tiles/ground.png");
}

void EditorState::InitModes()
{
    this->modes.push_back(new DefaultEditorMode(this->stateData, this->tileMap, &this->editorStateData));
    this->modes.push_back(new EnemyEditorMode(this->stateData, this->tileMap, &this->editorStateData));

    this->activeMode = DEFAULT_EDITOR_MODE;
}

EditorState::EditorState(StateData* stateData)
    : State(stateData)
{
    this->InitVariables();
    this->InitEditorStateData();
    this->InitView();
    this->InitFonts();
    this->InitKeybinds();
    this->InitPauseMenu();
    this->InitButtons();
    this->InitTileMap();
    this->InitGui();
    this->InitModes();
}

EditorState::~EditorState()
{
    auto it = this->buttons.begin();

    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
        delete it->second;

    delete this->pmenu;
    delete this->tileMap;

    for (size_t i = 0; i < this->modes.size(); i++)
        delete this->modes[i];
}

// Functions
void EditorState::UpdateInput(const float& dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->GetKeytime())
    {
        if (!this->paused || !this->showed)
        {
            this->PauseState();
            this->ShowedState();
        }
        else
        {
            this->UnpauseState();
            this->UnshowedState();
        }
    }
}

void EditorState::UpdateEditorInput(const float& dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
        this->view.move(0.f, -this->cameraSpeed * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
        this->view.move(-this->cameraSpeed * dt, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
        this->view.move(0.f, this->cameraSpeed * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
        this->view.move(this->cameraSpeed * dt, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MODE_UP"))))
    {
        if (this->activeMode < this->modes.size() - 1)
            ++this->activeMode;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MODE_DOWN"))))
    {
        if (this->activeMode > 0)
            --this->activeMode;
    }
}

void EditorState::UpdateButtons()
{
    for (auto& it : this->buttons)
        it.second->Update(this->mousePosWindow);

}

void EditorState::UpdateGui(const float& dt)
{

}

void EditorState::UpdatePauseMenuButtons()
{
    if (this->pmenu->IsButtonPressed("EXIT_STATE"))
        this->EndState();

    if (this->pmenu->IsButtonPressed("SAVE"))
        this->tileMap->SaveToFile("level_7.slmp");

    if (this->pmenu->IsButtonPressed("LOAD"))
        this->tileMap->LoadFromFile("level_7.slmp"); /*arcada*/
}

void EditorState::UpdateModes(const float& dt)
{
    this->modes[this->activeMode]->Update(dt);
}

void EditorState::Update(sf::Music* music, const float& dt)
{
    this->UpdateMousePositions(&this->view);
    this->Updatekeytime(dt);
    this->UpdateInput(dt);

    if (!this->paused || !this->showed)
    {
        this->UpdateButtons();
        this->UpdateGui(dt);
        this->UpdateEditorInput(dt);
        this->UpdateModes(dt);
    }
    else
    {
        this->pmenu->Update(this->mousePosWindow);
        this->UpdatePauseMenuButtons();
    }
}

void EditorState::RenderButtons(sf::RenderTarget& target)
{
    for (auto& it : this->buttons)
    {
        it.second->Render(target);
    }
}

void EditorState::RenderGui(sf::RenderTarget& target)
{

}

void EditorState::RenderModes(sf::RenderTarget& target)
{
    this->modes[this->activeMode]->Render(target);
}

void EditorState::Render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->setView(this->view);
    this->tileMap->Render(*target, this->mousePosGrid, NULL, sf::Vector2f());
    this->tileMap->DefferedRender(*target);

    target->setView(this->window->getDefaultView());

    this->RenderButtons(*target);

    this->RenderGui(*target);

    this->RenderModes(*target);

    if (this->paused || this->showed)
    {
        target->setView(this->window->getDefaultView());
        this->pmenu->Render(*target);
    }

}
