#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteObject.h"
#include "Game.h"

class Defence :
	public SpriteObject
{
public:
	Defence(GameDataRef data, int index, float startX, float startY);
	~Defence();

	void Update(float dt);
	void UpdateInput(float dt);
	void Draw();
	void Delete();
	void onDeath();

	int GetHealth();
	void SetHealth(int value);

	int getIndex() { return _index; }

	Collision GetCollision() { return Collision(_sprite); }
	sf::Sprite& GetSprite() { return _sprite; }

	spriteTypes GetSpriteType() { return DEFENCE; }

private:
	GameDataRef _data;
	sf::Sprite _sprite;
	sf::Clock _track;
	sf::Clock _missleCooldown;
	sf::Clock _restartCooldown;

	int _index;
	int _health = 4;

};

