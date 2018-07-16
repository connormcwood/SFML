#pragma once
#include <SFML\Graphics.hpp>
#include "SpriteObject.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	void AddSprite(SpriteObject* sprite);
	void AddSpriteToGarbage(SpriteObject* spritePtr);

	void Update(float dt);
	void Draw();
	void UpdateInput(float dt);

private:
	std::vector<SpriteObject*> sprites;
	std::vector<SpriteObject*> garbageCollection;
};

