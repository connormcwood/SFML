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
	void onDeath();
	void UpdateAnimation();
	bool onCollision() { return true; }
	int getIndex() { return _index; }

	spriteTypes GetSpriteType() { return INVADER; }

	Collision GetCollision() { return Collision(_invader); }
	sf::Sprite& GetSprite() { return _invader; }

	static void setDirection(int value);
	static int getDirection();

	static int getTotal();
	static void setTotal(int value);

	static int getDeadTotal();
	static void setDeadTotal(int value);

private:
	GameDataRef _data;
	sf::Sprite _invader;
	DeathObserver* _dealthObserverPtr;

	std::vector<Missle> Missles;
	std::map<int, sf::IntRect> _retrievedAnimation;

	sf::Sound death;

	std::string _textureName;
	int _animationStatus = 0;

	int _index;

	static int _deadInvaders;
	static int _totalInvaders;
	static int _direction; // -1 Left 0 Not Moving 1 Rgiht
	bool _canCollide = true;
};

