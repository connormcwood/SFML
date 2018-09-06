#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "pugixml.hpp"
#include <iostream>

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	void LoadTexture(std::string name, std::string fileName);
	sf::Texture &GetTexture(std::string name);
	void AddTexture(std::string name, std::string fileName);

	void LoadFont(std::string name, std::string fileName);
	sf::Font &GetFont(std::string name);

	int LoadSpriteSheet(std::string name, std::string fileName, const char* xmlFileName);
	sf::Image &GetSpriteSheet(std::string name);

	bool LoadSoundBuffer(std::string name, std::string fileName);
	sf::SoundBuffer& GetSoundBuffer(std::string name);

	void PlaySound(std::string name);

	bool LoadAssets();

	float GetStatus();
	void SetStatus(float value);

	float GetVolume();
	void SetVolume(float value);

	bool GetLoadedSpriteSheets();

	friend class SplashState;
	float _status;

private:
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;
	std::map<std::string, sf::Image> _spritesheets;
	std::map<std::string, sf::SoundBuffer> _sounds;

	sf::Sound _sound;

	bool _hasLoadedSpreadSheets;
	float _volume = 0.5;
};