#include "Invader.h"



Invader::Invader(GameDataRef data, float startX, float startY) : _data(data)
{
	_invader.setTexture(this->_data->assets.GetTexture("InvaderA2"));
	_invader.setOrigin(sf::Vector2f(_invader.getLocalBounds().width / 2, _invader.getLocalBounds().height / 2));
	_invader.setPosition(startX, startY);
}


Invader::~Invader()
{
}

void Invader::Update(float dt)
{
	if (_invader.getPosition().x == 768) {
		_direction = 0;
	}
	else if (_invader.getPosition().x == 0) {
		_direction = 1;
	}

	if (_direction == 0) {
		_invader.move(-1, 0);
	}
	else if (_direction == 1) {
		_invader.move(1, 0);
	}
}

void Invader::UpdateInput(float dt)
{
}

void Invader::Draw()
{
	this->_data->window.draw(_invader);
}