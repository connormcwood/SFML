#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "pugixml.hpp"
#include <iostream>

class AssetManager
{
public:
	AssetManager() { }
	~AssetManager() { }

	void LoadTexture(std::string name, std::string fileName);
	sf::Texture &GetTexture(std::string name);

	void LoadFont(std::string name, std::string fileName);
	sf::Font &GetFont(std::string name);

	void LoadSpriteSheet(std::string name, std::string fileName, const char* xmlFileName);
	sf::Image &GetSpriteSheet(std::string name);

private:
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;
	std::map<std::string, sf::Image> _spritesheets;
};