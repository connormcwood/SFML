#pragma once
#include <SFML\Graphics.hpp>
#include "State.h"
#include "Game.h"


class SplashState :
	public State
{
public:
	SplashState(GameDataRef data);
	~SplashState();

	void Init();
	void HandleInput(float dt);
	void Update(float dt);
	void Draw(float dt);
	void UpdateLoadingBar();

private:
	GameDataRef _data;
	sf::Clock _clock;
	sf::Sprite _background;
	sf::Sprite _test;

	sf::Clock _track;

	sf::RectangleShape _loadingBar;
	sf::RectangleShape _loadingBox;
};



