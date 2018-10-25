#pragma once
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "SpriteObject.h"
#include "Collision.h"
#include "Definitions.h"
#include "DeathObserver.h"

class Missle : public SpriteObject
{
public:
	Missle(GameDataRef data, float startX, float startY, bool isVertical);
	~Missle();

	void Update(float dt);
	void Draw();
	void UpdateInput(float dt);
	void Delete();
	void onDeath();
	int getIndex() { return 0; }

	spriteTypes GetSpriteType() { return MISSLE; }

	Collision GetCollision() { return Collision(_missle); }
	sf::Int32 GetLifespan() {
		_lifespan = _track.getElapsedTime();
		return _lifespan.asMilliseconds();
	}
	sf::Sprite& GetSprite() { return _missle;  }

	bool isVertical;

	static int getTotal();
	static void setTotal(int value);

private:
	GameDataRef _data;
	sf::Sprite _missle;
	sf::Clock _track;
	sf::Time _lifespan;

	bool toBeDeleted = false;

	static int _totalMissles;
	float _acceleration = 1.5f;
};

