#pragma once
#include "State.h"
#include "Game.h"
#include "Character.h"

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
	sf::Text text;

	Character *character;
};

