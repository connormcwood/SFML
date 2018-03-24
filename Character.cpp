#include "Character.h"
#include "Definitions.h"

Character::Character(GameDataRef data) : _data(data)
{

	_character.setTexture(this->_data->assets.GetTexture("spaceShips_004.png"));
	_character.setOrigin(sf::Vector2f(_character.getLocalBounds().width / 2, _character.getLocalBounds().height / 2));
	_character.setPosition(SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2);
}

Character::~Character()
{
}

void Character::UpdateInput(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (_playerVelocityX >= -PLAYER_MAX_SPEED) {
			_playerVelocityX += -PLAYER_ACCELERATION;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {		
		if (_playerVelocityX <= PLAYER_MAX_SPEED) {
			_playerVelocityX += PLAYER_ACCELERATION;
		}
	}

	sf::Time _elapsed = _missleCooldown.getElapsedTime();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _elapsed.asSeconds() > PLAYER_MISSLE_COOLDOWN) {
		Missles.push_back(Missle(_data, _character.getPosition().x - 36, _character.getPosition().y - 58));
		Missles.push_back(Missle(_data, _character.getPosition().x + 36, _character.getPosition().y - 58));
		_missleCooldown.restart();
	}
}

void Character::UpdateCharacter(float dt)
{
	for (std::vector<Missle>::reverse_iterator it = Missles.rbegin(); it != Missles.rend(); ++it) {
		it->Update(dt);
	}
	//std::cout << _character.getPosition().x << " " << _character.getPosition().y << " " << _playerVelocityX << std::endl;
	_character.move(sf::Vector2f(_playerVelocityX, 0));

	_playerPosX = _character.getPosition().x;
	_playerPosY = _character.getPosition().y;

	if (_playerVelocityX > 0.001) {
		_playerVelocityX -= PLAYER_ACCELERATION / 10;
	}
	else if (_playerVelocityX < -0.001) {
		_playerVelocityX += PLAYER_ACCELERATION / 10;
	}


	/*
	_velocity += _acceleration - (PLAYER_MOVEMENT_FRICTION * _velocity * _velocity);
	
	sf::Time _elapsed = _track.getElapsedTime();
	if (_elapsed.asSeconds() > 0.25)
	{
		if (_acceleration > 0.001) {
			_acceleration -= PLAYER_ACCELERATION;
		}
		else if (_acceleration < -0.001) {
			_acceleration += PLAYER_ACCELERATION;
		}

		if (_acceleration == 0.001 || _acceleration == -0.001) {
			_acceleration = 0;
		}
		_track.restart();
	}
	std::cout << _acceleration << " " << _velocity << " " << _character.getPosition().x << " " << std::endl;
	*/
}

void Character::DrawCharacter()
{
	for (std::vector<Missle>::reverse_iterator it = Missles.rbegin(); it != Missles.rend(); ++it) {
		it->Draw();
	}
	this->_data->window.draw(_character);
}
