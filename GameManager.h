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
	bool Clear();

	void SetFPS(float fps);
	float GetFPS();

	void CheckDirectionClear(int direction, bool strictObject);

	int GetScore();
	void SetScore(int value);

	int GetHealth();
	void SetHealth(int value);

private:
	std::vector<SpriteObject*> sprites;
	std::vector<SpriteObject*> garbageCollection;
	float _fps = 0;


	int _score = 0;
	int _health = 3;
};

