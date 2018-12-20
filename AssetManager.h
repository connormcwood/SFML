#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "pugixml.hpp"
#include <iostream>

class AnimationTexture;
class ImageTexture;
class Texture;

class AssetManager
{
private:
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;
	std::map<std::string, sf::Image> _spritesheets;
	std::map<std::string, sf::SoundBuffer> _sounds;
	
	std::map<std::string, std::map<int, sf::IntRect>> _animation;
	sf::Sound _sound;

	Texture * texture;
	AnimationTexture * animationTexture;
	ImageTexture * imageTexture;

	bool _hasLoadedSpreadSheets;
	float _volume = 0.5;

public:
	AssetManager();
	~AssetManager();

	void LoadTexture(std::string name, std::string fileName);
	sf::Texture &GetTexture(std::string name);
	void AddTexture(std::string name, std::string fileName, sf::IntRect intRect);
	void AddTexture(std::string name, std::string fileName);
	void AddTexture(std::string name, std::string fileName, int x, int y, int width, int height);

	void LoadFont(std::string name, std::string fileName);
	sf::Font &GetFont(std::string name);

	int LoadImageSpriteSheet(std::string name, std::string fileName, const char* xmlFileName);
	int LoadAnimationSpriteSheet(std::string name, std::string fileName, const char* xmlFileName);
	sf::Image &GetSpriteSheet(std::string name);

	bool LoadSoundBuffer(std::string name, std::string fileName);
	sf::SoundBuffer& GetSoundBuffer(std::string name);

	void SetAnimation(std::string name, sf::IntRect);
	sf::IntRect GetAnimation(std::string name, int index);
	size_t GetAnimationSize(std::string name);

	void PlaySound(std::string name);

	bool LoadAssets();

	float GetStatus();
	void SetStatus(float value);

	float GetVolume();
	void SetVolume(float value);

	bool GetLoadedSpriteSheets();

	friend class SplashState;
	friend class Texture;
	float _status;
};

