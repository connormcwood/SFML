#include "Missle.h"



Missle::Missle(GameDataRef data, float startX, float startY) : _data(data)
{
	_missle.setTexture(this->_data->assets.GetTexture("Bullet"));
	_missle.setOrigin(sf::Vector2f(_missle.getLocalBounds().width / 2, _missle.getLocalBounds().height / 2));
	_missle.setPosition(startX, startY);	
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

void Missle::UpdateInput(float dt)
{
}

void Missle::SetToBeDeleted(bool value)
{
	toBeDeleted = value;
}

bool Missle::GetToBeDeleted()
{
	return this->toBeDeleted;
}
