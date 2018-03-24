#pragma once
#include "SFML\Graphics.hpp"
#include "Game.h"
#include "Definitions.h"

class Missle
{
public:
	Missle(GameDataRef data, float x, float y);
	~Missle();

	void Update(float dt);
	void Draw();
private:
	GameDataRef _data;
	sf::Sprite _missle;
	sf::Clock _track;

	float _acceleration = 1.0f;
};

