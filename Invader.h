#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "SpriteObject.h"
#include "Missle.h"
#include "Collision.h"

class Invader : public SpriteObject
{
public:
	Invader(GameDataRef data, float startX, float startY);
	~Invader();

	void Update(float dt);
	void UpdateInput(float dt);
	void Draw();

private:
	GameDataRef _data;
	sf::Sprite _invader;
	sf::Clock _track;
	sf::Clock _missleCooldown;
	int _direction = 1; // E = 1 W = 0
	std::vector<Missle> Missles;
	Collision GetCollision() { return Collision(_invader); }
};

