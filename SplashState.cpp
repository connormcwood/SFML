#include "SplashState.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <functional>
#include <iostream>
#include <utility>
#include "AssetManager.h"
#include "Definitions.h"
#include "GameState.h"

SplashState::SplashState(GameDataRef data) : _data(data)
{

}

void SplashState::Init()
{
	this->_data->assets.LoadTexture("Splash State Background", SPLASH_STATE_BACKGROUND_FILEPATH);
	_background.setTexture(this->_data->assets.GetTexture("Splash State Background"));

	_loadingBox.setFillColor(sf::Color(0, 0, 0));
	_loadingBox.setOutlineColor(sf::Color(255, 255, 255));
	_loadingBox.setOutlineThickness(1);
	
	_loadingBar.setFillColor(sf::Color(255, 255, 255));
	
	_loadingBox.setOrigin(sf::Vector2f(255 / 2, 10 / 2));
	_loadingBar.setOrigin(sf::Vector2f(255 / 2, 10 / 2));

	_loadingBar.setPosition((SCREEN_WIDTH / 2) - (_loadingBar.getLocalBounds().width / 2), SCREEN_HEIGHT / 2);
	_loadingBox.setPosition((SCREEN_WIDTH / 2) - (_loadingBox.getLocalBounds().width / 2), SCREEN_HEIGHT / 2);

	_loadingBox.setSize(sf::Vector2f(255, 10));
	_loadingBar.setSize(sf::Vector2f(0, 10));

	std::thread t1(&AssetManager::LoadAssets, std::ref(this->_data->assets));
	t1.detach();

	std::cout << "Completed In Splash" << std::endl;
}

void SplashState::HandleInput(float dt)
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
	if (_elapsed.asSeconds() > 0.25)
	{	
		UpdateLoadingBar();
		_track.restart();
	}
	
	if (this->_data->assets._hasLoadedSpreadSheets == true)
	{
		std::cout << "Completed" << std::endl;
		_data->machine.AddState(StateRef(new GameState(_data)));
	}
}

void SplashState::Draw(float dt)
{
	this->_data->window.clear(sf::Color::Red);
	this->_data->window.draw(this->_background);
	this->_data->window.draw(this->_test);
	this->_data->window.draw(this->_loadingBox);
	this->_data->window.draw(this->_loadingBar);
	this->_data->window.display();
}

void SplashState::UpdateLoadingBar()
{
	float ratio = this->_data->assets.GetStatus() / 100;
	float total = _loadingBox.getLocalBounds().width * ratio;
	_loadingBar.setSize(sf::Vector2f(total, 10));
}
