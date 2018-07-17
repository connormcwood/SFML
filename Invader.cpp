#include "Invader.h"
#include <time.h> 


Invader::Invader(GameDataRef data, float startX, float startY) : _data(data)
{
	_invader.setTexture(this->_data->assets.GetTexture("InvaderA2"));
	_invader.setOrigin(sf::Vector2f(_invader.getLocalBounds().width / 2, _invader.getLocalBounds().height / 2));
	_invader.setPosition(startX, startY);
	srand(time(NULL));
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
	//	_invader.move(-1, 0);
	}
	else if (_direction == 1) {
	//	_invader.move(1, 0);
	}

	sf::Time _elapsed = _track.getElapsedTime();
	if (_elapsed.asSeconds() > 1 && (rand() % 10 + 1) == 3) {
		if (this->_data->manager.CheckDirectionClear(this, 3, false) == false) {
			this->_data->manager.AddSprite(new Missle(_data, _invader.getPosition().x, _invader.getPosition().y + 25, false));
		}
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