#include "Invader.h"
#include <time.h> 
#include "DeathObserver.h"

int Invader::_direction;
int Invader::_totalInvaders;

Invader::Invader(GameDataRef data, float startX, float startY) : _data(data)
{
	DeathObserver* dObsPtr = new DeathObserver(this, data);

	setTotal(getTotal() + 1);
	_index = getTotal();

	if (_index < 37) {
		this->_data->manager.addInvaderIndex(getIndex());
	}
	
	_invader.setTexture(this->_data->assets.GetTexture("invader_spritesheet"));
	_invader.setTextureRect(rectSourceSprite);

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

	sf::Time _elapsed = _track.getElapsedTime();
	sf::Time _animationElapsed = _animation.getElapsedTime();
	if (_animationElapsed.asSeconds() > 0.5) {
		if (rectSourceSprite.left == 0) {
			rectSourceSprite.left = 49;
		}
		else {
			rectSourceSprite.left = 0;
		}
		_invader.setTextureRect(rectSourceSprite);
		_animation.restart();
	}

	if (_elapsed.asSeconds() > 1 && rand() % 60 + 1 == 3 && this->_data->manager.indexExist(getIndex() + 9) == false) {
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

int Invader::getTotal()
{
	return _totalInvaders;
}

void Invader::setTotal(int value)
{
	_totalInvaders = value;
}
