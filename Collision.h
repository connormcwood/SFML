#pragma once
#include <SFML/Graphics.hpp>

class Collision
{
public:
	Collision(sf::Sprite& _sprite);
	~Collision();

	void Move(float dx, float dy) { _sprite.setPosition(dx, dy); }
	bool CheckCollision(Collision other, sf::Vector2f& direction, float push);
	sf::Vector2f GetPosition() { return _sprite.getPosition();  }
	sf::Vector2f GetHalfSize() { return _sprite.getPosition() / 2.0f; }
	sf::Sprite& GetSprite() { return _sprite;  }

private:
	sf::Sprite& _sprite;
};

