#include "stdafx.h"
#include "TextTagSystem.h"

// Initialize functions
void TextTagSystem::InitVariables()
{
}

void TextTagSystem::InitFonts(std::string fontFile)
{
	if (!this->font.loadFromFile(fontFile)) exit(01);
}

void TextTagSystem::InitTagTemplates()
{
	this->tagTemplates[TagTypes::DEFAULT_TAG] = new TextTag(this->font, "", 100.f, 100.f, -1.f, -0.5f, sf::Color::White, 25, 50.f, true, 200.f, 500.f, 2);
	this->tagTemplates[TagTypes::NEGATIVE_TAG] = new TextTag(this->font, "", 100.f, 100.f, -1.f, -0.5f, sf::Color::Red, 25, 50.f, true, 250.f, 500.f, 2);
	this->tagTemplates[TagTypes::EXPEREINCE_TAG] = new TextTag(this->font, "", 100.f, 100.f, 0.f, -0.5f, sf::Color::Blue, 35, 50.f, true, 250.f, 500.f, 2);
	this->tagTemplates[TagTypes::CRIT_TAG] = new TextTag(this->font, "", 100.f, 100.f, -1.f, -0.5f, sf::Color::Red, 45, 50.f, true, 250.f, 500.f, 2);
	this->tagTemplates[TagTypes::MISS_TAG] = new TextTag(this->font, "", 5.f, 5.f, -1.f, -0.5f, sf::Color::White, 25, 50.f, true, 250.f, 500.f, 2);
}

// Constructor/Destructor
TextTagSystem::TextTagSystem(std::string fontFile)
{
	this->InitFonts(fontFile);
	this->InitVariables();
	this->InitTagTemplates();

}

TextTagSystem::~TextTagSystem()
{
	for (auto* tag : this->tags)
		delete tag;

	for (auto& tag : this->tagTemplates)
		delete tag.second;
}

// Functions
void TextTagSystem::AddTextTag(const unsigned tagTypes, float posX, float posY, const std::string str, const std::string prefix, const std::string postfix)
{
	std::stringstream ss;
	ss << prefix << " " << str << " " << postfix;
	this->tags.push_back(new TextTag(this->tagTemplates[tagTypes], posX, posY, ss.str()));
}

void TextTagSystem::AddTextTag(const unsigned tagTypes, float posX, float posY, const int i, const std::string prefix, const std::string postfix)
{
	std::stringstream ss;
	ss << prefix << " " << i << " " << postfix;
	this->tags.push_back(new TextTag(this->tagTemplates[tagTypes], posX, posY, ss.str()));
}

void TextTagSystem::AddTextTag(const unsigned tagTypes, float posX, float posY, const float f, const std::string prefix, const std::string postfix)
{
	std::stringstream ss;
	ss << prefix << " " << f << " " << postfix;
	this->tags.push_back(new TextTag(this->tagTemplates[tagTypes], posX, posY, ss.str()));
}

void TextTagSystem::Update(const float& dt)
{
	for (size_t i = 0; i < this->tags.size(); i++)
	{
		this->tags[i]->Update(dt);

		if (this->tags[i]->IsExpired())
		{
			delete this->tags[i];
			this->tags.erase(this->tags.begin() + i);
		}
	}
}

void TextTagSystem::Render(sf::RenderTarget& target)
{
	for (auto& tag : this->tags)
		tag->Render(target);
}
