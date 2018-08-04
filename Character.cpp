#include "Character.h"
#include "Definitions.h"
#include "GameState.h"

Character::Character(GameDataRef data) : _data(data)
{

	_character.setTexture(this->_data->assets.GetTexture("Ship"));
	_character.setOrigin(sf::Vector2f(_character.getLocalBounds().width / 2, _character.getLocalBounds().height / 2));
	_character.setPosition(SCREEN_HEIGHT / 2, SCREEN_HEIGHT - 100);
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
		this->_data->manager.AddSprite(new Missle(_data, _character.getPosition().x, _character.getPosition().y - 25, true));
		_missleCooldown.restart();
	}

}

void Character::Delete()
{
	SetAlive(false);
	this->_data->manager.SetHealth(this->_data->manager.GetHealth() - 1);
	//this->_data->machine.AddState(StateRef(new GameState(_data)));
}

void Character::onDeath()
{
}

void Character::Update(float dt)
{
	_character.move(sf::Vector2f(_playerVelocityX, 0));

	if (_character.getPosition().x <= (LOWEST_SPRITE_X + 30)) {
		_character.setPosition(LOWEST_SPRITE_X + 30, _character.getPosition().y);
	}
	else if (_character.getPosition().x >= (HIGHEST_SPRITE_X - 30)) {
		_character.setPosition(HIGHEST_SPRITE_X - 30, _character.getPosition().y);
	}

	_playerPosX = _character.getPosition().x;
	_playerPosY = _character.getPosition().y;

	if (_playerVelocityX > 0.001) {
		_playerVelocityX -= PLAYER_ACCELERATION / 10;
	} 
	else if (_playerVelocityX < -0.001) {
		_playerVelocityX += PLAYER_ACCELERATION / 10;
	}
}

void Character::Draw()
{
	this->_data->window.draw(_character);
}
