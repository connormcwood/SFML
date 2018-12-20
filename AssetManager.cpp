#include "AssetManager.h"
#include "Definitions.h"
#include "ImageTexture.h"
#include "AnimationTexture.h"

AssetManager::AssetManager()
{
	std::cout << "Asset Manager Created" << std::endl;
	imageTexture = new ImageTexture();
	animationTexture = new AnimationTexture();
}

AssetManager::~AssetManager()
{
	delete imageTexture;
	delete animationTexture;
	delete texture;
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

void AssetManager::AddTexture(std::string name, std::string fileName, sf::IntRect intRect)
{
	sf::Texture tex;
	if (tex.loadFromFile(fileName, intRect)) {
		this->_textures[name] = tex;
	}
}

void AssetManager::AddTexture(std::string name, std::string fileName)
{
	sf::Texture tex;
	if (tex.loadFromFile(fileName)) {
		this->_textures[name] = tex;
	}
}

void AssetManager::AddTexture(std::string name, std::string fileName, int x, int y, int width, int height)
{
	sf::Texture tex;
	try {
		if (tex.loadFromFile(fileName, sf::IntRect(x, y, width, height))) {
			this->_textures[name] = tex;
		}
	}
	catch (int e) {
		throw e;
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
	LoadImageSpriteSheet("barrier_stylesheet", BARRIER_STYLESHEET_IMAGE, BARRIER_STYLESHEET_XML);
	LoadImageSpriteSheet("main_stylesheet", MAIN_STYLESHEET_IMAGE, MAIN_STYLESHEET_XML);
	LoadAnimationSpriteSheet("animation_stylesheet", ANIMATION_STYLESHEET_PATH, ANIMATION_STYLESHEET_XML);
	LoadAnimationSpriteSheet("invader_spritesheet", INVADER_STYLESHEET_PATH, INVADER_STYLESHEET_XML);
	LoadAnimationSpriteSheet("invader_spritesheet2", INVADER_STYLESHEET_PATH2, INVADER_STYLESHEET_XML2);
	LoadAnimationSpriteSheet("invader_spritesheet3", INVADER_STYLESHEET_PATH3, INVADER_STYLESHEET_XML3);

	LoadSoundBuffer("bang", SOUND_BANG_PATH);
	LoadSoundBuffer("explosion", SOUND_EXPLOSION_PATH);
	LoadSoundBuffer("invader_death", SOUND_INVADER_DEATH_PATH);
	LoadSoundBuffer("shoot", SOUND_SHOOT_PATH);

	AddTexture("invader_ufo", UFO_PATH, sf::IntRect(0, 0, 97, 32));
	AddTexture("sound_mute", MUTE_PATH, sf::IntRect(0, 0, 97, 32));
	AddTexture("sound_plus", MUTE_PLUS_PATH, sf::IntRect(0, 0, 97, 32));

	LoadFont("open_sans", "opensans.ttf");

	_hasLoadedSpreadSheets = true;
	return true;
}

int AssetManager::LoadImageSpriteSheet(std::string name, std::string fileName, const char* xmlFileName)
{
	texture = imageTexture;
	texture->LoadAssetManager(this);
	texture->CreateTextures(name, fileName, xmlFileName);

	return 1;
}

int AssetManager::LoadAnimationSpriteSheet(std::string name, std::string fileName, const char* xmlFileName)
{
	texture = animationTexture;
	texture->LoadAssetManager(this);
	texture->CreateTextures(name, fileName, xmlFileName);

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
