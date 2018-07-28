#include "Invader.h"
#include <time.h> 
#include "DeathObserver.h"

int Invader::_direction;

Invader::Invader(GameDataRef data, float startX, float startY) : _data(data)
{
	DeathObserver* dObsPtr = new DeathObserver(this, data);
	std::cout << "Invader: " << this << std::endl;
 	_invader.setTexture(this->_data->assets.GetTexture("InvaderA2"));
	_invader.setOrigin(sf::Vector2f(_invader.getLocalBounds().width / 2, _invader.getLocalBounds().height / 2));
	_invader.setPosition(startX, startY);

	setDirection(1);

	srand(time(NULL));
}


Invader::~Invader()
{
}

void Invader::Update(float dt)
{
	if (_direction == -1) {
		_invader.setPosition(_invader.getPosition().x - 1, _invader.getPosition().y + this->_data->manager.getVerticalOffset());
	}
	else if (_direction == 1) {
		_invader.setPosition(_invader.getPosition().x + 1, _invader.getPosition().y + this->_data->manager.getVerticalOffset());
	}

	if (_invader.getPosition().x == HIGHEST_SPRITE_X) {
		setDirection(-1);
		this->_data->manager.setReachedSide(true);
	}
	else if (_invader.getPosition().x == LOWEST_SPRITE_X) {
		setDirection(1);
		this->_data->manager.setReachedSide(true);
	}

	sf::Time _elapsed = _track.getElapsedTime();
	if (_elapsed.asSeconds() > 1 && GetCanFire() == true) {
		this->_data->manager.AddSprite(new Missle(_data, _invader.getPosition().x, _invader.getPosition().y + 25, false));
		_track.restart();
	}
}

void Invader::UpdateInput(float dt)
{
}

void Invader::Draw()
{
	this->_data->window.draw(_invader);
}

void Invader::Delete()
{
	this->_data->manager.SetScore(this->_data->manager.GetScore() + 1);
	SetAlive(false);
}

void Invader::setDirection(int value)
{
	_direction = value;
}

int Invader::getDirection()
{
	return _direction;
}
