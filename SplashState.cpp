#include "SplashState.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <functional>
#include <iostream>
#include <utility>
#include "AssetManager.h"
#include "Definitions.h"

SplashState::SplashState(GameDataRef data) : _data(data)
{

}

void SplashState::Init()
{
	this->_data->assets.LoadTexture("Splash State Background", SPLASH_STATE_BACKGROUND_FILEPATH);
	_background.setTexture(this->_data->assets.GetTexture("Splash State Background"));

	std::thread t1(&AssetManager::LoadSpriteSheets, std::ref(this->_data->assets));
	t1.detach();

	std::cout << "Completed In Splash" << std::endl;
	

	/*_test.setTexture(this->_data->assets.GetTexture("spaceShips_001.png"));
	_test.setPosition((SCREEN_WIDTH / 2) - (_test.getGlobalBounds().width / 2), _test.getGlobalBounds().height / 2);*/
		
	//std::thread t2(&SplashState::LoadXML, this);
	
	/*_test.setTexture(this->_data->assets.GetTexture("spaceAstronauts_001.png"));
	_test.setPosition((SCREEN_WIDTH / 2) - (_test.getGlobalBounds().width / 2), _test.getGlobalBounds().height / 2);*/
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
	sf::Time _elapsed = _track.getElapsedTime();
	if (_elapsed.asSeconds() > 1)
	{	
		std::cout << this->_data->assets.GetStatus() << std::endl;
		std::cout << _elapsed.asSeconds() << std::endl;
		_track.restart();
	}

	if (this->_data->assets._hasLoadedSpreadSheets == true)
	{
		std::cout << "True" << std::endl;
	}

	if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
	{
			//std::cout << "Switch to Main" << std::endl;
	}
}

void SplashState::Draw(float dt)
{
	this->_data->window.clear(sf::Color::Red);

	this->_data->window.draw(this->_background);
	this->_data->window.draw(this->_test);
	this->_data->window.display();
}
