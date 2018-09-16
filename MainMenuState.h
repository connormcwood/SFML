#pragma once
#include <SFML\Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "Definitions.h"
#include "GameState.h"
#include <string>

class MainMenuState :
	public State
{
public:
	MainMenuState(GameDataRef data);
	~MainMenuState();

	void Init();
	void HandleInput(float dt);
	void Update(float dt);
	void Draw(float dt);

	std::string TrimStr(std::string str);
private:
	GameDataRef _data;

	sf::Font * font;
	sf::Text volumeText;

	sf::Sprite _background;
	sf::Sprite _title;
	sf::Sprite _playButton;

	sf::Sprite _soundPlusButton;
	sf::Sprite _soundMuteButton;

	bool _hasPressed;
};

