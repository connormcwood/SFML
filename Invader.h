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
	void Delete();

	Collision GetCollision() { return Collision(_invader); }
	sf::Sprite& GetSprite() { return _invader; }

	static void setDirection(int value);
	static int getDirection();

private:
	GameDataRef _data;
	sf::Sprite _invader;
	sf::Clock _track;
	sf::Clock _missleCooldown;
	std::vector<Missle> Missles;

	static int _direction; // -1 Left 0 Not Moving 1 Rgiht
};

