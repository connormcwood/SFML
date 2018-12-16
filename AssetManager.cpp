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
	LoadSpriteSheet("barrier_stylesheet", BARRIER_STYLESHEET_IMAGE, BARRIER_STYLESHEET_XML);
	LoadSpriteSheet("main_stylesheet", MAIN_STYLESHEET_IMAGE, MAIN_STYLESHEET_XML);
	LoadSpriteSheet("animation_stylesheet", ANIMATION_STYLESHEET_PATH, ANIMATION_STYLESHEET_XML);
	LoadSpriteSheet("invader_spritesheet", INVADER_STYLESHEET_PATH, INVADER_STYLESHEET_XML);
	LoadSpriteSheet("invader_spritesheet2", INVADER_STYLESHEET_PATH2, INVADER_STYLESHEET_XML2);
	LoadSpriteSheet("invader_spritesheet3", INVADER_STYLESHEET_PATH3, INVADER_STYLESHEET_XML3);

	LoadSoundBuffer("bang", SOUND_BANG_PATH);
	LoadSoundBuffer("explosion", SOUND_EXPLOSION_PATH);
	LoadSoundBuffer("invader_death", SOUND_INVADER_DEATH_PATH);
	LoadSoundBuffer("shoot", SOUND_SHOOT_PATH);

	//AddTexture("invader_spritesheet", INVADER_STYLESHEET_PATH);
	//AddTexture("invader_spritesheet2", INVADER_STYLESHEET_PATH2);
	//AddTexture("invader_spritesheet3", INVADER_STYLESHEET_PATH3);


	AddTexture("invader_ufo", UFO_PATH);

	AddTexture("sound_mute", MUTE_PATH);
	AddTexture("sound_plus", MUTE_PLUS_PATH);

	LoadFont("open_sans", "opensans.ttf");

	std::cout << GetAnimation("Collision", 1).left << std::endl;

	_hasLoadedSpreadSheets = true;
	std::cout << "Loaded." << std::endl;
	return true;
}

int AssetManager::LoadSpriteSheet(std::string name, std::string fileName, const char* xmlFileName)
{
	sf::Texture tex;
	pugi::xml_document doc;

	if (!doc.load_file(xmlFileName)) {
		std::cout << "Couldnt Load" << std::endl;
	}

	pugi::xml_node textures = doc.child("textureatlas");

	float total = textures.select_nodes("subtexture").size();
	float iteration = 0;

	for (pugi::xml_node group = textures.child("regularTexture"); group; group = group.next_sibling("regularTexture")) {
		for (pugi::xml_node texture = group.child("subtexture"); texture; texture = texture.next_sibling("subtexture"))
		{

			int x = std::stoi(texture.attribute("x").value());
			int y = std::stoi(texture.attribute("y").value());
			int width = std::stoi(texture.attribute("width").value());
			int height = std::stoi(texture.attribute("height").value());

			if (tex.loadFromFile(fileName, sf::IntRect(x, y, width, height))) {
				this->_textures[texture.attribute("name").value()] = tex;
			}
			_status = (iteration / total) * 100;
			SetStatus(_status);
			iteration++;
		}
	}

	for (pugi::xml_node group = textures.child("animationTexture"); group; group = group.next_sibling("animationTexture")) {
		std::string name = group.attribute("name").value();

		for (pugi::xml_node texture = group.child("subtexture"); texture; texture = texture.next_sibling("subtexture"))
		{
			int x = std::stoi(texture.attribute("x").value());
			int y = std::stoi(texture.attribute("y").value());
			int width = std::stoi(texture.attribute("width").value());
			int height = std::stoi(texture.attribute("height").value());



			SetAnimation(name, sf::IntRect(x, y, width, height));
			
			_status = (iteration / total) * 100;
			SetStatus(_status);
			iteration++;
		}

		if (tex.loadFromFile(fileName)) {
			this->_textures[name] = tex;
		}
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

void AssetManager::SetAnimation(std::string name, sf::IntRect positions)
{
	this->_animation[name].insert(std::pair<int, sf::IntRect>(GetAnimationSize(name), positions));
}

sf::IntRect AssetManager::GetAnimation(std::string name, int index)
{
	return this->_animation[name].at(index);
}

size_t AssetManager::GetAnimationSize(std::string name)
{
	return this->_animation[name].size();
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
	std::cout << value << std::endl;
	if (value >= 100) {
		value = 100;
	}
	else if (value <= 0) {
		value = 0;
	}
	else {
		_volume = value;
	}
}

float AssetManager::GetVolume()
{
	return _volume;
}

bool AssetManager::GetLoadedSpriteSheets()
{
	return this->_hasLoadedSpreadSheets;
}
