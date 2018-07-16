#include "Collision.h"
#include <iostream>


Collision::Collision(sf::Sprite& _sprite) :
	_sprite(_sprite)
{

}


Collision::~Collision()
{
}

bool Collision::CheckCollision(Collision other, sf::Vector2f& direction, float push)
{
	
	if (GetSprite().getGlobalBounds().intersects(other.GetSprite().getGlobalBounds())) {
		return true;
	}
	return false;
}
