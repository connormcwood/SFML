#include "AssetManager.h"
#include "Definitions.h"

AssetManager::AssetManager()
{
	std::cout << "Asset Manager Created" << std::endl;
}

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

bool AssetManager::LoadSpriteSheets()
{
	LoadSpriteSheet("main_stylesheet", MAIN_STYLESHEET_IMAGE, MAIN_STYLESHEET_XML);
	_hasLoadedSpreadSheets = true;
	std::cout << "Loaded." << std::endl;
	return true;
}

int AssetManager::LoadSpriteSheet(std::string name, std::string fileName, const char* xmlFileName)
{
	pugi::xml_document doc;
	if (!doc.load_file(xmlFileName)) {
		std::cout << "Couldnt Load" << std::endl;
	}

	pugi::xml_node textures = doc.child("TextureAtlas");
			
	std::cout << textures.select_nodes("SubTexture").size() << std::endl;
	float total = textures.select_nodes("SubTexture").size();
	float iteration = 0;

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
		_status = (iteration / total) * 100;
		SetStatus(_status);
		iteration++;
	}

	sf::Image image;
	if (image.loadFromFile(fileName))
	{
		this->_spritesheets[name] = image;
	}

	return 1;
}

sf::Image & AssetManager::GetSpriteSheet(std::string name)
{
	return this->_spritesheets.at(name);
}

float AssetManager::GetStatus()
{
	std::cout << "Get Status " << _status << std::endl;
	return _status;
}

void AssetManager::SetStatus(float value)
{
	this->_status = value;
}

bool AssetManager::GetLoadedSpriteSheets()
{
	return this->_hasLoadedSpreadSheets;
}
