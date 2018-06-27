#pragma once
#include "SFML\Graphics.hpp"
#include "Game.h"
#include "Collision.h"
#include "Definitions.h"

class Missle
{
public:
	Missle(GameDataRef data, sf::Sprite _parent, float offsetX, float offsetY);
	~Missle();

	void Update(float dt);
	void Draw();
	void DeleteMissle();
	void SetToBeDeleted(bool value);
	bool GetToBeDeleted();
	Collision GetCollision() { return Collision(_missle); }

private:
	GameDataRef _data;
	sf::Sprite _missle;
	sf::Clock _track;

	bool toBeDeleted = false;

	float _acceleration = 0.1f;
};

