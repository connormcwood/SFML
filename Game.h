#pragma once

#include <memory>
#include <string>
#include <SFML\Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "GameManager.h"

struct GameData
{
	StateMachine machine;
	sf::RenderWindow window;
	sf::View view;
	AssetManager assets;
	InputManager input;
	GameManager manager;
};


typedef std::shared_ptr<GameData> GameDataRef;

class Game
{
public:
	Game(int width, int height, std::string title);

private: 
	const float _updatesPerSec = 60;
	sf::Clock _clock;

	GameDataRef _data = std::make_shared<GameData>();

	void Run();
};

