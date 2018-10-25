#include "Defence.h"

Defence::Defence(GameDataRef data, int index, float startX, float startY)
	: _data(data)
{
	std::string texture_name;
	if (index == 0) {
		texture_name = "Barrier_LeftTop";
	}
	else if (index == 2) {
		texture_name = "Barrier_RightTop";
	}
	else if (index == 4) {
		texture_name = "Barrier_Middle";
	}
	else {
		texture_name = "Barrier_Full";
	}

	_sprite.setTexture(this->_data->assets.GetTexture(texture_name));
	_sprite.setOrigin(sf::Vector2f(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2));
	_sprite.setPosition(startX, startY);
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
