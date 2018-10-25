#pragma once
#include "SpriteObject.h"

class SpriteManager
{
public:
	SpriteManager();
	~SpriteManager();

	bool CanCollide(spriteTypes a, spriteTypes b) {
		if (a != MISSLE && a == b) {
			return false;
		}
		return true;
	}

	bool CloseDistance(sf::Vector2f a, sf::Vector2f b) {
		return true;
	}
};

