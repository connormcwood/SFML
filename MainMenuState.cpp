#include "MainMenuState.h"

MainMenuState::MainMenuState(GameDataRef data) : _data(data)
{
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::Init()
{
	font = new sf::Font();
	if (!(*font).loadFromFile("opensans.ttf")) {
		std::cout << "Couldnt Load Font" << std::endl;
	}

	_soundPlusButton.setTexture(this->_data->assets.GetTexture("sound_plus"));
	_soundMuteButton.setTexture(this->_data->assets.GetTexture("sound_mute"));

	_soundPlusButton.setPosition(SCREEN_WIDTH - 40, SCREEN_HEIGHT - 50);
	_soundPlusButton.setScale(sf::Vector2f(1.5f, 1.5f));

	_soundMuteButton.setPosition(SCREEN_WIDTH - 80, SCREEN_HEIGHT - 50);
	_soundMuteButton.setScale(sf::Vector2f(1.5f, 1.5f));

	volumeText = sf::Text();
	volumeText.setFont(*font);
	volumeText.setCharacterSize(12);
	volumeText.setFillColor(sf::Color::White);
	volumeText.setPosition(10, 10);
	volumeText.setString("Volume: " + TrimStr(std::to_string(this->_data->assets.GetVolume())));
}

void MainMenuState::HandleInput(float dt)
{
	sf::Event event;
	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
	{
		if (!_hasPressed) {
			sf::Vector2i position = sf::Mouse::getPosition(this->_data->window);
			sf::Vector2f worldPos = this->_data->window.mapPixelToCoords(position);
			if (_soundMuteButton.getGlobalBounds().contains(worldPos)) {
				this->_data->assets.SetVolume(this->_data->assets.GetVolume() - 2);
			}
			if (_soundPlusButton.getGlobalBounds().contains(worldPos)) {
				this->_data->assets.SetVolume(this->_data->assets.GetVolume() + 2);
			}
			_hasPressed = true;
		}
	}
	else {
		_hasPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		this->_data->manager.Clear();
		this->_data->machine.AddState(StateRef(new GameState(_data)));
	}

	this->_data->manager.UpdateInput(dt);
}

void MainMenuState::Update(float dt)
{
	volumeText.setString("Volume: " + TrimStr(std::to_string(this->_data->assets.GetVolume())));
}

void MainMenuState::Draw(float dt)
{
	this->_data->window.clear(sf::Color::Black);
	this->_data->window.draw(volumeText);
	this->_data->window.draw(_soundPlusButton);
	this->_data->window.draw(_soundMuteButton);
	this->_data->window.display();
}

std::string MainMenuState::TrimStr(std::string str)
{
	bool reachedDecimal = false;
	for (std::string::size_type s = 0; s < str.length(); s++) {
		if (str[s] == '.') {
			reachedDecimal = true;
		}

		if(str[s] == '0' & reachedDecimal == true) {
			str.erase(s, str.length() - s);
		}
	}
	return str;
}
