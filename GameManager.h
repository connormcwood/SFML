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
	
	void SetFPS(float fps);
	float GetFPS();

	bool CheckDirectionClear(SpriteObject* sprite, int direction, bool strictObject);

private:
	std::vector<SpriteObject*> sprites;
	std::vector<SpriteObject*> garbageCollection;
	float _fps = 0;
};

