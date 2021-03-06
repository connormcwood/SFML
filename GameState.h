#pragma once
#include "State.h"
#include "Game.h"
#include "Character.h"
#include "MainMenuState.h"
#include <SFML/Graphics.hpp>

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
	void Destroy();

private:
	GameDataRef _data;
	sf::Clock _clock;
	float _charSpeed;
	int _direction;
	int _prevDirection;
	
	sf::Text fpsText;
	sf::Text scoreText;
	sf::Text healthText;
	sf::Text spriteText;
	sf::Font * font;

	Character *character;
};

