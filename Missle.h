#pragma once
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "SpriteObject.h"
#include "Collision.h"
#include "Definitions.h"

class Missle : public SpriteObject
{
public:
	Missle(GameDataRef data, float startX, float startY, bool isVertical);
	~Missle();

	void Update(float dt);
	void Draw();
	void UpdateInput(float dt);

	Collision GetCollision() { return Collision(_missle); }
	sf::Int32 GetLifespan() {
		_lifespan = _track.getElapsedTime();
		return _lifespan.asMilliseconds();
	}
	sf::Sprite& GetSprite() { return _missle;  }

	bool isVertical;

private:
	GameDataRef _data;
	sf::Sprite _missle;
	sf::Clock _track;
	sf::Time _lifespan;

	bool toBeDeleted = false;

	float _acceleration = 1.0f;
};

