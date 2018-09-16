#include "GameState.h"
#include "Definitions.h"
#include "Character.h"
#include "Invader.h"
#include "Ufo.h"

GameState::GameState(GameDataRef data) : _data(data)
{
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));



}

GameState::~GameState()
{
}

void GameState::Init()
{
	font = new sf::Font();
	if (!(*font).loadFromFile("opensans.ttf")) {
		std::cout << "Couldnt Load Font" << std::endl;
	}


	fpsText = sf::Text();
	fpsText.setFont(*font);
	fpsText.setCharacterSize(12);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setPosition(10, 10);

	scoreText = sf::Text();
	scoreText.setFont(*font);
	scoreText.setCharacterSize(14);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100);

	healthText = sf::Text();
	healthText.setFont(*font);
	healthText.setCharacterSize(14);
	healthText.setFillColor(sf::Color::Red);
	healthText.setPosition(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 80);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 9; j++) {
			this->_data->manager.AddSprite(new Invader(_data, (j * 55.0f) + 155.0f, (i * 50.0f) + 100.0f));
		}
	}

	this->_data->manager.AddSprite(new Ufo(_data, SCREEN_WIDTH / 2, 50));

	this->_data->manager.AddSprite(new Character(_data));

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
		this->_data->manager.Clear();
		this->_data->machine.AddState(StateRef(new MainMenuState(_data)));
	}

	this->_data->manager.UpdateInput(dt);
}

void GameState::Update(float dt)
{

	fpsText.setString(std::to_string(this->_data->manager.getFPS()));
	scoreText.setString("score: " + std::to_string(this->_data->manager.getScore()));
	healthText.setString("health: " + std::to_string(this->_data->manager.getHealth()));
	this->_data->manager.Update(dt);
}

void GameState::Draw(float dt)
{
	this->_data->window.clear(sf::Color::Black);
	this->_data->manager.Draw();
	this->_data->window.draw(fpsText);
	this->_data->window.draw(scoreText);
	this->_data->window.draw(healthText);
	this->_data->window.display();

}
