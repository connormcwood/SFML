
#include <SFML\Graphics.hpp>
#include "Definitions.h"
#include "Game.h"

#include <iostream>

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
}

