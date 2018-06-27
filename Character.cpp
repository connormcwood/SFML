#include "Character.h"
#include "Definitions.h"

Character::Character(GameDataRef data) : _data(data)
{

	_character.setTexture(this->_data->assets.GetTexture("spaceShips_004.png"));
	_character.setOrigin(sf::Vector2f(_character.getLocalBounds().width / 2, _character.getLocalBounds().height / 2));
	_character.setPosition(SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2);

	for (int i = 0; i < 5; i++) {
		Missles.push_back(Missle(_data, _character, (i * 20), 500));
		Missles.push_back(Missle(_data, _character, -(i * 40), 500));
	}
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
		Missles.push_back(Missle(_data, _character, -36, -64));
		Missles.push_back(Missle(_data, _character, 36, -64));
		_missleCooldown.restart();
	}

}

void Character::UpdateCharacter(float dt)
{
	sf::Vector2f direction;
	for (std::vector<Missle>::iterator it = Missles.begin(); it != Missles.end(); ++it) {
		it->Update(dt);
		if (GetCollision().CheckCollision(it->GetCollision(), direction, 0.0f)) {
				std::cout << "Deleting - " << (it - Missles.begin()) << std::endl;
				it = Missles.erase(it);
				if (it != Missles.begin()) {
					it = std::prev(it);
					continue;
				}			
		}
	}


	_character.move(sf::Vector2f(_playerVelocityX, 0));

	_playerPosX = _character.getPosition().x;
	_playerPosY = _character.getPosition().y;

	if (_playerVelocityX > 0.001) {
		_playerVelocityX -= PLAYER_ACCELERATION / 10;
	} 
	else if (_playerVelocityX < -0.001) {
		_playerVelocityX += PLAYER_ACCELERATION / 10;
	}
}

void Character::DrawCharacter()
{
	for (std::vector<Missle>::reverse_iterator it = Missles.rbegin(); it != Missles.rend(); ++it) {
		it->Draw();
	}
	this->_data->window.draw(_character);
}
