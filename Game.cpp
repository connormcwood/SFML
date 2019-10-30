#include "Game.h"
#include "SplashState.h"

Game::Game(int width, int height, std::string title)
{

	_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);
	_data->window.setKeyRepeatEnabled(false);
	_data->machine.AddState(StateRef(new SplashState(_data)));
	this->Run();
}

void Game::Run()
{
	
	float interpolation;

	float skipTicks = 1000 / _updatesPerSec;
	float nextUpdate = this->_clock.getElapsedTime().asMilliseconds();
	float currentTime = this->_clock.getElapsedTime().asMilliseconds();

	while (this->_data->window.isOpen())
	{
		currentTime = this->_clock.getElapsedTime().asMilliseconds();
		
		this->_data->machine.ProcessStateChanges();

		while (nextUpdate < currentTime) {
			float deltaTime = nextUpdate - currentTime;
			this->_data->machine.GetActiveState()->HandleInput(deltaTime);
			this->_data->machine.GetActiveState()->Update(deltaTime);

			nextUpdate += skipTicks;
		}

		interpolation = (currentTime + skipTicks - nextUpdate) / skipTicks;
		this->_data->manager.setFPS(1.0f / (nextUpdate - currentTime) );
		this->_data->machine.GetActiveState()->Draw(interpolation);
	}
	
}
