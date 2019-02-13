#include "Ufo.h"
#include <time.h> 
#include <SFML\Audio.hpp>

int Ufo::_direction;
int Ufo::_totalUfos;
int Ufo::_deadUfos;

Ufo::Ufo(GameDataRef data, float startX, float startY) : _data(data)
{
	_dealthObserverPtr = new DeathObserver(this, data);

	Ufo::setTotal(Ufo::getTotal() + 1);
	_index = Ufo::getTotal();

	_Ufo.setTexture(this->_data->assets.GetTexture("invader_ufo"));

	_Ufo.setOrigin(sf::Vector2f(_Ufo.getLocalBounds().width / 2, _Ufo.getLocalBounds().height / 2));
	_Ufo.setPosition(startX, startY);

	setDirection(-1);

	srand(time(NULL));
}


Ufo::~Ufo()
{

}

void Ufo::Update(float dt)
{
	if (_direction == -1) {
		_Ufo.setPosition(_Ufo.getPosition().x - 0.75, _Ufo.getPosition().y + this->_data->manager.getVerticalOffset());
	}
	else if (_direction == 1) {
		_Ufo.setPosition(_Ufo.getPosition().x + 0.75, _Ufo.getPosition().y + this->_data->manager.getVerticalOffset());
	}

	if (_Ufo.getPosition().x == (HIGHEST_SPRITE_X - _Ufo.getLocalBounds().width / 2) ) {
		setDirection(-1);
		this->_data->manager.setReachedSide(true);
	}
	else if (_Ufo.getPosition().x == (LOWEST_SPRITE_X - _Ufo.getLocalBounds().width / 2) ) {
		setDirection(1);
		this->_data->manager.setReachedSide(true);
	}

	sf::Time _elapsed = _track.getElapsedTime();

	if (_elapsed.asSeconds() > 1 && rand() % 60 + 1 == 3 && (Missle::getTotal() < MAX_MISSLE) && this->_data->manager.indexExist(getIndex() + 9) == false) {
		std::cout << Missle::getTotal() << std::endl;
		//this->_data->manager.AddSprite(new Missle(_data, _Ufo.getPosition().x, _Ufo.getPosition().y + 25, false));
		_track.restart();
	}
}

void Ufo::UpdateInput(float dt)
{
}

void Ufo::Draw()
{
	this->_data->window.draw(_Ufo);
}

void Ufo::Delete()
{
	Detach(_dealthObserverPtr);
	delete _dealthObserverPtr;
	SetAlive(false);
}

void Ufo::onDeath()
{
	this->_data->assets.PlaySound("invader_death");
	this->_data->manager.setScore(this->_data->manager.getScore() + 10);
}

void Ufo::setDirection(int value)
{
	_direction = value;
}

int Ufo::getDirection()
{
	return _direction;
}

int Ufo::getTotal()
{
	return _totalUfos;
}

void Ufo::setTotal(int value)
{
	_totalUfos = value;
}

int Ufo::getDeadTotal()
{
	return _deadUfos;
}

void Ufo::setDeadTotal(int value)
{
	_deadUfos = value;
}
