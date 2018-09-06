#include "AssetManager.h"
#include "Definitions.h"

AssetManager::AssetManager()
{
	std::cout << "Asset Manager Created" << std::endl;
}

AssetManager::~AssetManager()
{
	//_sounds.clear();

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

void AssetManager::AddTexture(std::string name, std::string fileName)
{
	sf::Texture tex;
	if (tex.loadFromFile(fileName, sf::IntRect(0, 0, 97, 32))) {
		this->_textures[name] = tex;
	}
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

bool AssetManager::LoadAssets()
{
	LoadSpriteSheet("main_stylesheet", MAIN_STYLESHEET_IMAGE, MAIN_STYLESHEET_XML);
	LoadSoundBuffer("bang", SOUND_BANG_PATH);
	LoadSoundBuffer("explosion", SOUND_EXPLOSION_PATH);
	LoadSoundBuffer("invader_death", SOUND_INVADER_DEATH_PATH);
	LoadSoundBuffer("shoot", SOUND_SHOOT_PATH);

	AddTexture("invader_spritesheet", INVADER_STYLESHEET_PATH);
	AddTexture("invader_spritesheet2", INVADER_STYLESHEET_PATH2);
	AddTexture("invader_spritesheet3", INVADER_STYLESHEET_PATH3);
	AddTexture("invader_ufo", UFO_PATH);

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

	pugi::xml_node textures = doc.child("textureatlas");

	float total = textures.select_nodes("subtexture").size();
	float iteration = 0;

	for (pugi::xml_node texture = textures.child("subtexture"); texture; texture = texture.next_sibling("subtexture"))
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

bool AssetManager::LoadSoundBuffer(std::string name, std::string fileName)
{
	sf::SoundBuffer sound = sf::SoundBuffer();

	if (!sound.loadFromFile(fileName)) {
		return false;
	}

	this->_sounds[name] = sound;

	return true;
}

sf::SoundBuffer & AssetManager::GetSoundBuffer(std::string name)
{
	return this->_sounds.at(name);
}

void AssetManager::PlaySound(std::string name)
{
	_sound.setBuffer(GetSoundBuffer(name));
	_sound.setVolume(GetVolume());
	_sound.play();
}

float AssetManager::GetStatus()
{
	return _status;
}

void AssetManager::SetStatus(float value)
{
	this->_status = value;
}

void AssetManager::SetVolume(float value)
{
	_volume = value;
}

float AssetManager::GetVolume()
{
	return _volume;
}

bool AssetManager::GetLoadedSpriteSheets()
{
	return this->_hasLoadedSpreadSheets;
}
