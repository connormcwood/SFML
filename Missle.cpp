#include "Missle.h"

int Missle::_totalMissles;

Missle::Missle(GameDataRef data, SpriteObject* parent,  float startX, float startY, bool isVertical) 
	: _data(data), isVertical(isVertical)
{
	_dealthObserverPtr = new DeathObserver(this, data);
	SetSpriteObjectPtr(parent);
	_missle.setTexture(this->_data->assets.GetTexture("Bullet"));
	_missle.setOrigin(sf::Vector2f(_missle.getLocalBounds().width / 2, _missle.getLocalBounds().height / 2));
	_missle.setPosition(startX, startY);	

	Missle::setTotal(Missle::getTotal() + 1);

	this->_data->assets.PlaySound("shoot");
}


Missle::~Missle()
{

}

void Missle::Update(float dt)
{
	float _velocityX;
	if (isVertical == true) {
		_velocityX = -1 * (_acceleration * _acceleration);
	}
	else {
		_velocityX = 1 * (_acceleration * _acceleration);
	}
	
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

void Missle::Delete()
{
	SetAlive(false);
}

void Missle::onDeath()
{
	GetSpriteObjectPtr()->SetSpriteObjectPtr(nullptr);
	delete _dealthObserverPtr;

	setTotal(Missle::getTotal() - 1);
}

int Missle::getTotal()
{
	return _totalMissles;
}

void Missle::setTotal(int value)
{
	_totalMissles = value;
}
