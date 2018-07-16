#include "Character.h"
#include "Definitions.h"

Character::Character(GameDataRef data) : _data(data)
{

	_character.setTexture(this->_data->assets.GetTexture("Ship"));
	_character.setOrigin(sf::Vector2f(_character.getLocalBounds().width / 2, _character.getLocalBounds().height / 2));
	_character.setPosition(SCREEN_HEIGHT / 2, SCREEN_HEIGHT - 100);

	

	/*for (int i = 0; i < 5; i++) {
		Missles.push_back(Missle(_data, _character, (i * 20), 500));
		Missles.push_back(Missle(_data, _character, -(i * 40), 500));
	}*/
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
		this->_data->manager.AddSprite(new Missle(_data, _character.getPosition().x, _character.getPosition().y - 25));
		_missleCooldown.restart();		
	}

}

void Character::Update(float dt)
{
	sf::Vector2f direction;
	
	//Ensure Missles Exist
	if(Missles.begin() != Missles.end()){
		for (std::vector<Missle>::iterator it = Missles.begin(); it != Missles.end(); ++it) {
			it->Update(dt);
			if (GetCollision().CheckCollision(it->GetCollision(), direction, 0.0f) && it->GetLifespan() > 800) {
				it = Missles.erase(it);
				if (it != Missles.begin()) {
					it = std::prev(it);
					continue;
				}
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

void Character::Draw()
{
	this->_data->window.draw(_character);
}
