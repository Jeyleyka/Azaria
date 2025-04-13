#include"stdafx.h"
#include "SettingsState.h"

// Initializer functions
void SettingsState::InitVariables()
{
    this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::InitFonts()
{
    if (!this->font.loadFromFile("Fonts/font3.ttf")) exit(3);
}

void SettingsState::InitValue()
{
    const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

    if (!this->volumeTexture.loadFromFile("Resources/Other/volume-up.png")) exit(02);

    this->volumeSprite.setTexture(this->volumeTexture);
    this->volumeSprite.setPosition(GUI::p2pX(11.0f, vm), GUI::p2pY(55.7f, vm));

    this->volumeBack.setFillColor(sf::Color::Black);
    this->volumeBack.setSize(sf::Vector2f(GUI::p2pX(11.9f, this->stateData->gfxSettings->resolution), GUI::p2pY(4.76f, this->stateData->gfxSettings->resolution)));
    this->volumeBack.setPosition(GUI::p2pX(18.5452f, vm), GUI::p2pY(55.8f, vm));

    this->volumeInner.setFillColor(sf::Color::White);
    this->volumeInner.setSize(sf::Vector2f(this->music->getVolume() * 2, GUI::p2pY(4.76f, this->stateData->gfxSettings->resolution)));
    this->volumeInner.setPosition(this->volumeBack.getPosition());
}

void SettingsState::InitKeybinds()
{
    std::ifstream ifs("Config/menustate_key.txt");

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

void SettingsState::InitGui()
{
    const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

    this->background.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));

    if (!this->bgTex.loadFromFile("Resources/Images/Backgrounds/menubg.jpg")) exit(3);

    this->background.setTexture(&this->bgTex);

    this->specialFont.loadFromFile("Fonts/font.ttf");

    this->buttons["INCREASE_VOLUME"] = new GUI::Button(
        GUI::p2pX(10.3f, vm), GUI::p2pY(49.f, vm), GUI::p2pX(12.f, vm), GUI::p2pY(12.f, vm),
        &this->font, "+", GUI::calcCharSize(vm, 30),
        sf::Color(212, 153, 2, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50), // 212 153 2 - orange
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    this->buttons["DECREASE_VOLUME"] = new GUI::Button(
        GUI::p2pX(26.3f, vm), GUI::p2pY(49.f, vm), GUI::p2pX(12.f, vm), GUI::p2pY(12.f, vm),
        &this->font, "-", GUI::calcCharSize(vm, 30),
        sf::Color(212, 153, 2, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50), // 212 153 2 - orange
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    this->buttons["EXIT_STATE"] = new GUI::Button(
        GUI::p2pX(83.3f, vm), GUI::p2pY(83.8f, vm), GUI::p2pX(14.8f, vm), GUI::p2pY(6.1f, vm),
        &this->font, "Back", GUI::calcCharSize(vm),
        sf::Color(212, 153, 2, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50), // 212 153 2 - orange
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    this->buttons["APPLY"] = new GUI::Button(
        GUI::p2pX(71.4f, vm), GUI::p2pY(83.8f, vm), GUI::p2pX(14.8f, vm), GUI::p2pY(6.1f, vm),
        &this->font, "Apply", GUI::calcCharSize(vm),
        sf::Color(212, 153, 2, 255), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50), // 212 153 2 - orange
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    std::vector<std::string> modesStr;

    for (auto& i : this->modes)
        modesStr.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));

    this->resolutionList["RESOLUTION"] = new GUI::DropDownList(GUI::p2pX(18.6f, vm), GUI::p2pY(41.8f, vm), GUI::p2pX(11.9f, vm),
        GUI::p2pY(4.7f, vm), specialFont, modesStr.data(), static_cast<unsigned>(modesStr.size()));

    this->fullscrean.push_back("Yes");
    this->fullscrean.push_back("No");

    this->fullscreanList["FULLSCREAN"] = new GUI::DropDownList(GUI::p2pX(18.6f, vm), GUI::p2pY(48.8f, vm), GUI::p2pX(11.9f, vm),
        GUI::p2pY(4.7f, vm), specialFont, this->fullscrean.data(), 2);

    this->optionsText.setFont(this->font);
    this->optionsText.setPosition(sf::Vector2f(GUI::p2pX(5.9f, vm), GUI::p2pY(42.8f, vm)));
    this->optionsText.setCharacterSize(GUI::calcCharSize(vm, 91));
    this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));
    this->optionsText.setString("Resolution\n\nFullscreen\n\nMusic\n");
}

void SettingsState::ResetGui()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); it++)
        delete it->second;

    this->buttons.clear();

    auto it2 = this->resolutionList.begin();
    for (it2 = this->resolutionList.begin(); it2 != this->resolutionList.end(); it2++)
        delete it2->second;

    this->resolutionList.clear();

    auto it3 = this->fullscreanList.begin();
    for (it3 = this->fullscreanList.begin(); it3 != this->fullscreanList.end(); it3++)
        delete it3->second;

    this->fullscreanList.clear();
    this->InitGui();
    this->InitValue();
}

SettingsState::SettingsState(sf::Music* music, StateData* stateData)
    : State(stateData), music(music)
{
    this->InitVariables();
    this->InitFonts();
    this->InitValue();
    this->InitKeybinds();
    this->InitGui();
    this->ResetGui();
}

SettingsState::~SettingsState()
{
    auto i = this->buttons.begin();

    for (i = this->buttons.begin(); i != this->buttons.end(); ++i)
        delete i->second;

    auto it = this->resolutionList.begin();

    for (it = this->resolutionList.begin(); it != this->resolutionList.end(); ++it)
        delete it->second;

    auto it2 = this->fullscreanList.begin();

    for (it2 = this->fullscreanList.begin(); it2 != this->fullscreanList.end(); ++it2)
        delete it2->second;
}

// Functions
void SettingsState::UpdateInput(const float& dt)
{

}

void SettingsState::UpdateVolume(sf::Music* music, float volumeChange)
{
    if (this->buttons["INCREASE_VOLUME"]->IsPressed())
    {
        this->music->setVolume(this->music->getVolume() + 1.f);
        this->volumeInner.setSize(sf::Vector2f(this->volumeInner.getSize().x + 2.f, GUI::p2pY(4.76f, this->stateData->gfxSettings->resolution)));

        if (this->volumeInner.getSize().x >= 200.f)
            this->volumeInner.setSize(sf::Vector2f(GUI::p2pX(11.9f, this->stateData->gfxSettings->resolution), GUI::p2pY(4.76f, this->stateData->gfxSettings->resolution)));
    }
    else if (this->buttons["DECREASE_VOLUME"]->IsPressed())
    {
        this->music->setVolume(this->music->getVolume() - 1.f);
        this->volumeInner.setSize(sf::Vector2f(this->volumeInner.getSize().x - 2.f, GUI::p2pY(4.76f, this->stateData->gfxSettings->resolution)));

        if (this->volumeInner.getSize().x <= 0.f)
            this->volumeInner.setSize(sf::Vector2f(0.f, GUI::p2pY(4.76f, this->stateData->gfxSettings->resolution)));
    }

    //float volume = this->music->getVolume();

    //volume += volumeChange;

    //// Проверяем, чтобы громкость была в пределах допустимого диапазона (0-100)
    if (this->music->getVolume() < 0.f) {
        this->music->setVolume(0.f);
        this->volumeInner.setSize(sf::Vector2f(0.f, GUI::p2pY(4.76f, this->stateData->gfxSettings->resolution)));
    }
    else if (this->music->getVolume() > 100) {
        this->music->setVolume(100.f);
        this->volumeInner.setSize(sf::Vector2f(GUI::p2pX(11.9f, this->stateData->gfxSettings->resolution), GUI::p2pY(4.76f, this->stateData->gfxSettings->resolution)));
    }

    //this->music->setVolume(volume);

}

void SettingsState::UpdateGui(const float& dt)
{
    for (auto& it : this->buttons)
    {
        it.second->Update(this->mousePosWindow);
    }

    if (this->buttons["EXIT_STATE"]->IsPressed())
        this->EndState();

    if (this->buttons["APPLY"]->IsPressed())
    {
        this->stateData->gfxSettings->resolution = this->modes[this->resolutionList["RESOLUTION"]->GetActiveElementId()];

        if (this->fullscreanList["FULLSCREAN"]->GetActiveElementId() == 0)
            this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Fullscreen);
        else
            this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
        this->ResetGui();
    }


    for (auto& it : this->resolutionList)
    {
        it.second->Update(this->mousePosWindow, dt);
    }

    for (auto& it : this->fullscreanList)
    {
        it.second->Update(this->mousePosWindow, dt);
    }
}

void SettingsState::Update(sf::Music* music, const float& dt)
{
    this->UpdateMousePositions();
    this->UpdateInput(dt);
    this->UpdateVolume(music, 10.f);

    /*if (this->buttons["INCREASE_VOLUME"]->IsPressed())
       this->UpdateVolume(music, 10.f);
    else if (this->buttons["INCREASE_VOLUME"]->IsPressed())
       this->UpdateVolume(music, -10.f);*/

    this->UpdateGui(dt);

}

void SettingsState::RenderGui(sf::RenderTarget& target)
{
    for (auto& it : this->buttons)
        it.second->Render(target);

    for (auto& it : this->resolutionList)
        it.second->Render(target);

    for (auto& it : this->fullscreanList)
        it.second->Render(target);
}

void SettingsState::RenderValue(sf::RenderTarget& target)
{
    target.draw(this->volumeBack);
    target.draw(this->volumeInner);
    target.draw(this->volumeSprite);
}

void SettingsState::Render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(this->background);

    this->RenderValue(*target);
    this->RenderGui(*target);
    target->draw(this->optionsText);

    sf::Text mouseText;
    mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50.f);
    mouseText.setFont(this->font);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    mouseText.setString(ss.str());

    target->draw(mouseText);
}
