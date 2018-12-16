#include "Defence.h"

Defence::Defence(GameDataRef data, int index, float startX, float startY)
	: _data(data)
{
	switch (index) {
		case 0:
			texture_name = "Barrier_LeftTop";
			break;
		case 2:
			texture_name = "Barrier_RightTop";
			break;
		case 4:
			texture_name = "Barrier_Middle";
			break;
		default:
			texture_name = "Barrier_Full";
			break;
	}

	_sprite.setTexture(this->_data->assets.GetTexture(texture_name));
	_sprite.setOrigin(sf::Vector2f(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2));
	_sprite.setPosition(startX, startY);

	_retrievedAnimation.insert(std::pair<int, sf::IntRect>(_retrievedAnimation.size(), this->_data->assets.GetAnimation("Collision", 0)));
	_retrievedAnimation.insert(std::pair<int, sf::IntRect>(_retrievedAnimation.size(), this->_data->assets.GetAnimation("Collision", 1)));
	_retrievedAnimation.insert(std::pair<int, sf::IntRect>(_retrievedAnimation.size(), this->_data->assets.GetAnimation("Collision", 2)));
	_retrievedAnimation.insert(std::pair<int, sf::IntRect>(_retrievedAnimation.size(), this->_data->assets.GetAnimation("Collision", 3)));

	_collisionSprite.setOrigin(sf::Vector2f(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2));
	_collisionSprite.setPosition(startX, startY);

	_collisionSprite.setTexture(this->_data->assets.GetTexture("Collision"));
	_collisionSprite.setTextureRect(_retrievedAnimation[_animationIndex]);
}

Defence::~Defence()
{
}

void Defence::Update(float dt)
{
}

void Defence::UpdateInput(float dt)
{
}

void Defence::Draw()
{
	this->_data->window.draw(_sprite);
	if (GetHealth() < 5) {
		this->_data->window.draw(_collisionSprite);
	}
}

void Defence::Delete()
{
}

void Defence::onDeath()
{
	SetHealth(GetHealth() - 1);
}

int Defence::GetHealth()
{
	return _health;
}

void Defence::SetHealth(int value)
{
	_health = value;
}
