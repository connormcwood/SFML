#include "SplashState.h"
#include <iostream>
#include <sstream>

#include "Definitions.h"
SplashState::SplashState(GameDataRef data) : _data(data)
{

}

void SplashState::Init()
{
	this->_data->assets.LoadTexture("Splash State Background", SPLASH_STATE_BACKGROUND_FILEPATH);
	_background.setTexture(this->_data->assets.GetTexture("Splash State Background"));

	LoadXML();

	_test.setTexture(this->_data->assets.GetTexture("spaceAstronauts_001.png"));
	_test.setPosition((SCREEN_WIDTH / 2) - (_test.getGlobalBounds().width / 2), _test.getGlobalBounds().height / 2);
}

void SplashState::HandleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}
	}
}

void SplashState::Update(float dt)
{
	if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
	{
		if (_status == 100)
		{
			std::cout << "Switch to Main" << std::endl;
		}
	}
}

void SplashState::Draw(float dt)
{
	this->_data->window.clear(sf::Color::Red);

	this->_data->window.draw(this->_background);
	this->_data->window.draw(this->_test);
	this->_data->window.display();
}

int SplashState::LoadXML()
{
	this->_data->assets.LoadSpriteSheet("main_stylesheet", MAIN_STYLESHEET_IMAGE, MAIN_STYLESHEET_XML);
	return 0;
}
