#include "Character.h"
#include "Definitions.h"

Character::Character(GameDataRef data) : _data(data)
{

	_character.setTexture(this->_data->assets.GetTexture("spaceShips_004.png"));
	_character.setOrigin(sf::Vector2f(_character.getLocalBounds().width / 2, _character.getLocalBounds().height / 2));
	_character.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50);
}

Character::~Character()
{
}

void Character::UpdateCharacter()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		_character.move(sf::Vector2f(-2, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		_character.move(sf::Vector2f(2, 0));
	}
}

void Character::DrawCharacter()
{
	this->_data->window.draw(_character);
}
