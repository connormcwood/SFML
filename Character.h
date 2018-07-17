#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteObject.h"
#include "Game.h"
#include "Missle.h"
#include "Collision.h"


class Character : public SpriteObject
{
public:
	Character(GameDataRef data);
	~Character();

	void Update(float dt);
	void Draw();
	void UpdateInput(float dt);
	sf::Sprite& GetSprite() { return _character; }

private:
	GameDataRef _data;
	sf::Sprite _character;
	sf::Clock _track;
	sf::Clock _missleCooldown;
	Collision GetCollision() { return Collision(_character); }


	float _direction = 0;
	bool _hasInput = false;

	float _acceleration = 0.0;
	float _velocity = 0.0;

	float _playerPosX = _character.getPosition().x;
	float _playerPosY = _character.getPosition().y;

	float _playerVelocityX = 0;
	float _playerVelocityY = 0;
};

