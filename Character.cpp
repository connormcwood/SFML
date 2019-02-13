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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (_playerVelocityX >= -PLAYER_MAX_SPEED) {
			_playerVelocityX += -PLAYER_ACCELERATION;
		}
	} 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (_playerVelocityX <= PLAYER_MAX_SPEED) {
			_playerVelocityX += PLAYER_ACCELERATION;
		}
	}

	sf::Time _elapsed = _missleCooldown.getElapsedTime();
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) && _elapsed.asSeconds() > PLAYER_MISSLE_COOLDOWN && GetSpriteObjectPtr() == nullptr) {
		SpriteObject* _misslePtr = new Missle(_data, this, _character.getPosition().x, _character.getPosition().y - 25, true);
		SetSpriteObjectPtr(_misslePtr);
		this->_data->manager.AddSprite(_misslePtr);
		_missleCooldown.restart();
	}

}

void Character::Delete()
{
	this->_data->manager.setHealth(this->_data->manager.getHealth() - 1);
	this->_data->manager.setPaused(true);
	sf::Time _elapsed = _restartCooldown.getElapsedTime();
	if (this->_data->manager.getHealth() == 0) {
		this->_data->machine.AddState(StateRef(new MainMenuState(_data)));
	}
	else {
		while (_elapsed.asSeconds() > 3) {
			this->_data->machine.AddState(StateRef(new GameState(_data)));
			break;
		}
	}
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
