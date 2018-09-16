#pragma once
#include "State.h"
#include "Game.h"
#include "Character.h"
#include "MainMenuState.h"

class GameState :
	public State
{
public:
	GameState(GameDataRef data);
	~GameState();

	void Init();
	void HandleInput(float dt);
	void Update(float dt);
	void Draw(float dt);

private:
	GameDataRef _data;
	sf::Clock _clock;
	float _charSpeed;
	int _direction;
	int _prevDirection;
	
	sf::Text fpsText;
	sf::Text scoreText;
	sf::Text healthText;
	sf::Font * font;

	Character *character;
};

