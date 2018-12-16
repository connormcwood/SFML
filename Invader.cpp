#include "Invader.h"
#include <time.h> 
#include "DeathObserver.h"
#include <SFML\Audio.hpp>

int Invader::_direction;
int Invader::_totalInvaders;
int Invader::_deadInvaders;

Invader::Invader(GameDataRef data, float startX, float startY) : _data(data)
{
	DeathObserver* dObsPtr = new DeathObserver(this, data);

	Invader::setTotal(Invader::getTotal() + 1);
	_index = Invader::getTotal();

	if (_index < 37) {
		this->_data->manager.addInvaderIndex(Invader::getIndex());
	}

	if (_index <= 9) {
		_textureName = "Invader";
	}
	else if(_index >= 10 && _index <= 27) {
		_textureName = "Invader2";
	}
	else {
		_textureName = "Invader3";
	}

	_retrievedAnimation.insert(std::pair<int, sf::IntRect>(_retrievedAnimation.size(), this->_data->assets.GetAnimation(_textureName, 0)));
	_retrievedAnimation.insert(std::pair<int, sf::IntRect>(_retrievedAnimation.size(), this->_data->assets.GetAnimation(_textureName, 1)));

	_invader.setTexture(this->_data->assets.GetTexture(_textureName));
	_invader.setTextureRect(_retrievedAnimation[0]);

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
		_invader.setPosition(_invader.getPosition().x - 0.5, _invader.getPosition().y + this->_data->manager.getVerticalOffset());
	}
	else if (_direction == 1) {
		_invader.setPosition(_invader.getPosition().x + 0.5, _invader.getPosition().y + this->_data->manager.getVerticalOffset());
	}

	if (_invader.getPosition().x == HIGHEST_SPRITE_X) {
		setDirection(-1);
		this->_data->manager.setReachedSide(true);
	}
	else if (_invader.getPosition().x == LOWEST_SPRITE_X) {
		setDirection(1);
		this->_data->manager.setReachedSide(true);
	}

	if (GetSpriteObjectPtr() == nullptr && rand() % 100 + 1 == 7 && (Missle::getTotal() < MAX_MISSLE) && this->_data->manager.indexExist(getIndex() + 9) == false) {
		SpriteObject* misslePtr = new Missle(_data, this, _invader.getPosition().x, _invader.getPosition().y + 25, false);
		SetSpriteObjectPtr(misslePtr);
		this->_data->manager.AddSprite(misslePtr);
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
	SetAlive(false);
}

void Invader::onDeath()
{	
	this->_data->assets.PlaySound("invader_death");
	Invader::setDeadTotal(Invader::getDeadTotal() + 1);
	this->_data->manager.setScore(this->_data->manager.getScore() + 1);
	this->_data->manager.removeInvaderIndex(getIndex());
}

void Invader::UpdateAnimation()
{
	_invader.setTextureRect(_retrievedAnimation[_animationStatus]);
	if (_animationStatus == 0) {
		_animationStatus = 1;
	}
	else {
		_animationStatus = 0;
	}
}

void Invader::setDirection(int value)
{
	_direction = value;
}

int Invader::getDirection()
{
	return _direction;
}

int Invader::getTotal()
{
	return _totalInvaders;
}

void Invader::setTotal(int value)
{
	_totalInvaders = value;
}

int Invader::getDeadTotal()
{
	return _deadInvaders;
}

void Invader::setDeadTotal(int value)
{
	_deadInvaders = value;
}
