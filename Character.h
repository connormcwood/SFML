#pragma once
#include "SFML\Graphics.hpp"
#include "Game.h"
#include "Missle.h"
#include "Collision.h"

class Character
{
public:
	Character(GameDataRef data);
	~Character();

	void UpdateCharacter(float dt);
	void DrawCharacter();
	void UpdateInput(float dt);

private:
	GameDataRef _data;
	sf::Sprite _character;
	sf::Clock _track;
	sf::Clock _missleCooldown;
	std::vector<Missle> Missles;
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

