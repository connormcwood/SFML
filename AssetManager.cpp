#include "AssetManager.h"
#include "Definitions.h"
void AssetManager::LoadTexture(std::string name, std::string fileName)
{
	sf::Texture tex;

	if (tex.loadFromFile(fileName))
	{
		this->_textures[name] = tex;
	}
}

sf::Texture &AssetManager::GetTexture(std::string name)
{
	return this->_textures.at(name);
}

void AssetManager::LoadFont(std::string name, std::string fileName)
{
	sf::Font font;

	if (font.loadFromFile(fileName))
	{
		this->_fonts[name] = font;
	}
}

sf::Font &AssetManager::GetFont(std::string name)
{
	return this->_fonts.at(name);
}

void AssetManager::LoadSpriteSheet(std::string name, std::string fileName, const char* xmlFileName)
{
	sf::Image image;
	if (image.loadFromFile(fileName))
	{
		this->_spritesheets[name] = image;
	}

	pugi::xml_document doc;
	if (!doc.load_file(xmlFileName)) {
		std::cout << "Couldnt Load" << std::endl;
	}

	pugi::xml_node textures = doc.child("TextureAtlas");
			
	for (pugi::xml_node texture = textures.child("SubTexture"); texture; texture = texture.next_sibling("SubTexture"))
	{
		sf::Texture tex;

		std::string x = texture.attribute("x").value();
		std::string y = texture.attribute("y").value();
		std::string width = texture.attribute("width").value();
		std::string height = texture.attribute("height").value();

		if (tex.loadFromFile(MAIN_STYLESHEET_IMAGE, sf::IntRect(std::stoi(x), std::stoi(y), std::stoi(width), std::stoi(height)))){
			this->_textures[texture.attribute("name").value()] = tex;
		}
	}

	

}

sf::Image & AssetManager::GetSpriteSheet(std::string name)
{
	return this->_spritesheets.at(name);
}
