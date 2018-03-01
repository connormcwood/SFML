#include "GameState.h"
#include "Definitions.h"
#include "Character.h"


GameState::GameState(GameDataRef data) : _data(data)
{
}

GameState::~GameState()
{
}

void GameState::Init()
{
	character = new Character(_data);
}

// direction 1 - N, 2 - E, 3 - S, 4 - W

void GameState::HandleInput()
{
	sf::Event event;
	character->UpdateCharacter();
	while (this->_data->window.pollEvent(event))
	{

		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}
	}
}

void GameState::Update(float dt)
{

}

void GameState::Draw(float dt)
{
	this->_data->window.clear(sf::Color::Black);
	character->DrawCharacter();
	this->_data->window.display();
}
