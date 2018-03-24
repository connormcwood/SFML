#include "Missle.h"



Missle::Missle(GameDataRef data, float x, float y) : _data(data)
{
	_missle.setTexture(this->_data->assets.GetTexture("spaceMissiles_001.png"));
	_missle.setOrigin(sf::Vector2f(_missle.getLocalBounds().width / 2, _missle.getLocalBounds().height / 2));
	_missle.setPosition(x, y);
}


Missle::~Missle()
{
}

void Missle::Update(float dt)
{
	float _velocityX = -1 * (_acceleration * _acceleration);

	_missle.move(0, _velocityX);
	sf::Time _elapsed = _track.getElapsedTime();
	if (_elapsed.asSeconds() > 0.25) {
		_acceleration += 0.05;
	}
}

void Missle::Draw()
{
	this->_data->window.draw(_missle);
}
