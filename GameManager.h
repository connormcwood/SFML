#pragma once
#include <SFML\Graphics.hpp>
#include "SpriteObject.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	bool AddSprite(SpriteObject* sprite);
	void Update(float dt);
	void Draw();
	void UpdateInput(float dt);

private:
	std::vector<SpriteObject*> sprites;
};

