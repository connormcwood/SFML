#include "GameState.h"
#include "Definitions.h"
#include "Character.h"


GameState::GameState(GameDataRef data) : _data(data)
{
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
}

GameState::~GameState()
{
}

void GameState::Init()
{
	character = new Character(_data);
}

// direction 1 - N, 2 - E, 3 - S, 4 - W

void GameState::HandleInput(float dt)
{
	sf::Event event;
	while (this->_data->window.pollEvent(event))
	{

		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		_data->machine.AddState(StateRef(new GameState(_data)));
	}

	character->UpdateInput(dt);
}

void GameState::Update(float dt)
{
	character->UpdateCharacter(dt);
}

void GameState::Draw(float dt)
{
	this->_data->window.clear(sf::Color::Black);
	character->DrawCharacter();
	this->_data->window.display();
}
