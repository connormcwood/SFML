
#include <SFML\Graphics.hpp>
#include "Definitions.h"
#include "Game.h"

#include <iostream>
#include "Player.h"
#include "Platform.h"

static const float VIEW_HEIGHT = 512.0f;
static const float VIEW_WIDTH = 512.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Random Game");

	return 0;

	/*
	sf::RenderWindow window(sf::VideoMode(512, 512), "SFML Tutorial", sf::Style::Default);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));

	sf::Texture playerTexture;
	sf::Sprite playerImage;

	if (!playerTexture.loadFromFile("resources/orc.png")) {
		std::cout << "Couldn\'t Load Spritesheet" << std::endl;
	}
 	Player player(&playerTexture, sf::Vector2u(5, 3), 0.1f, 100.0f, 200.0f);
	 
	std::vector<Platform> platforms;
	platforms.push_back(Platform(nullptr, sf::Vector2f(500.0f, 10.0f), sf::Vector2f(0.0f, 500.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(500.0f, 10.0f), sf::Vector2f(500.0f, 500.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(500.0f, 10.0f), sf::Vector2f(1000.0f, 500.0f)));

	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 30.0f)
			deltaTime = 1.0f / 30.0f;


		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				printf("New window %i width, %i height.", event.size.width, event.size.height);
				break;
			}
		}

		player.Update(deltaTime);

		sf::Vector2f direction;

		for (Platform& platform : platforms)
			if (platform.GetCollision().CheckCollision(player.GetCollision(), direction, 1.0f))
				player.OnCollision(direction);
		/*
		platform1.GetCollision().CheckCollision(player.GetCollision(), 0.0f);
		platform2.GetCollision().CheckCollision(player.GetCollision(), 1.0f); */
	/*
		view.setCenter(player.GetPosition());


		window.clear(sf::Color(150, 150, 150));
		window.setView(view);
		
		player.Draw(window);
		for (Platform& platform : platforms)
			platform.Draw(window);

		window.display();
	}*/

	return 0;
}

