#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "SpriteObject.h"
#include "Missle.h"
#include "Collision.h"
#include "DeathObserver.h"

class Ufo : public SpriteObject
{
public:
	Ufo(GameDataRef data, float startX, float startY);
	~Ufo();

	void Update(float dt);
	void UpdateInput(float dt);
	void Draw();
	void Delete();
	void onDeath();
	void UpdateAnimation() { }
	bool onCollision() { return true;  }
	int getIndex() { return _index; }

	spriteTypes GetSpriteType() { return UFO; }

	Collision GetCollision() { return Collision(_Ufo); }
	sf::Sprite& GetSprite() { return _Ufo; }


	static void setDirection(int value);
	static int getDirection();

	static int getTotal();
	static void setTotal(int value);

	static int getDeadTotal();
	static void setDeadTotal(int value);

private:
	GameDataRef _data;
	sf::Sprite _Ufo;
	sf::Clock _track;
	sf::Clock _animation;
	sf::Clock _missleCooldown;
	std::vector<Missle> Missles;
	DeathObserver * _dealthObserverPtr;

	sf::Sound death;

	int _index;

	static int _deadUfos;
	static int _totalUfos;
	static int _direction; // -1 Left 0 Not Moving 1 Rgiht
};

