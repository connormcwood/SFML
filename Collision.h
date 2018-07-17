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
	sf::Vector2f GetHalfSize() { 
		sf::Vector2f size;
		size.x = _sprite.getGlobalBounds().width / 2.0f;
		size.y = _sprite.getGlobalBounds().height / 2.0f;
		return size;
	}
	sf::Sprite& GetSprite() { return _sprite;  }
	bool CheckIfDirectionFree(Collision other, int direction);

private:
	sf::Sprite& _sprite;
};

