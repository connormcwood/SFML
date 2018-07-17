#include "GameState.h"
#include "Definitions.h"
#include "Character.h"
#include "Invader.h"

GameState::GameState(GameDataRef data) : _data(data)
{
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

}

GameState::~GameState()
{
}

void GameState::Init()
{
	this->_data->manager.AddSprite(new Character(_data));


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 9; j++) {
			this->_data->manager.AddSprite(new Invader(_data, (j * 55.0f) + 155.0f, (i * 50.0f) + 100.0f));
		}
	}
	//this->_data->manager.AddSprite(new Invader(_data, (1 * 55.0f) + 155.0f, (1 * 50.0f) + 100.0f));
}

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

	this->_data->manager.UpdateInput(dt);
}

void GameState::Update(float dt)
{
	
	this->_data->manager.Update(dt);
}

void GameState::Draw(float dt)
{
	sf::Text text;
	sf::Font font;
	if (!font.loadFromFile("opensans.ttf")) {
		std::cout << "Couldnt Load Font" << std::endl;
	}
	text = sf::Text();
	text.setFont(font);
	text.setCharacterSize(12);
	text.setFillColor(sf::Color::White);
	text.setPosition(10, 10);
	text.setString(std::to_string(this->_data->manager.GetFPS()));

	this->_data->window.clear(sf::Color::Black);
	this->_data->manager.Draw();
	this->_data->window.draw(text);
	this->_data->window.display();

}
