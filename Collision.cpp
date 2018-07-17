#include "Collision.h"
#include <iostream>
#include <cmath>

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

bool Collision::CheckIfDirectionFree(Collision other, int direction)
{
	sf::FloatRect SpriteBounds = GetSprite().getGlobalBounds();

	if (direction == 1) {
		SpriteBounds.top = SpriteBounds.top - 40;
	}
	else if (direction == 2) {
		SpriteBounds.left = SpriteBounds.left - 40;
	}
	else if (direction == 3) {
		SpriteBounds.top = SpriteBounds.top + 40;
	}
	else if (direction == 4) {
		SpriteBounds.left = SpriteBounds.left + 40;
	}

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(SpriteBounds.width, SpriteBounds.height));
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(5);
	rectangle.setPosition(SpriteBounds.left, SpriteBounds.top);


	if(other.GetSprite().getGlobalBounds().intersects(SpriteBounds)) {
		return true;
	}
	return false;
}
