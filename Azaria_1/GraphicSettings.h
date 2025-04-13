#pragma once

class GraphicSettings
{
public:
	GraphicSettings();

	//Variables
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

	//Functions
	void SaveToFile(const std::string path);
	void LoadFromFile(const std::string path);
};