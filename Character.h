#pragma once
#include "SFML\Graphics.hpp"
#include "Game.h"


class Character
{
public:
	Character(GameDataRef data);
	~Character();

	void UpdateCharacter();
	void DrawCharacter();

private:
	GameDataRef _data;
	sf::Sprite _character;
};

