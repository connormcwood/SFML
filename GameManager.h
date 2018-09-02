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

	void setFPS(float fps);
	float getFPS();

	void CheckDirectionClear(int direction, bool strictObject);

	void setVerticalOffset(int value);
	int	getVerticalOffset();

	int getHealth();
	void setHealth(int value);

	int getScore();
	void setScore(int value);

	bool getReachedSide();
	void setReachedSide(bool value);

	void addInvaderIndex(int index);
	void removeInvaderIndex(int index);
	bool indexExist(int index);
	void clearInvaderIndex();

private:
	std::vector<SpriteObject*> sprites;
	std::vector<SpriteObject*> garbageCollection;
	std::vector<int> invaderIndex;
	float _fps = 0;


	int _score = 0;
	int _health = 3;

	int _verticalOffset;

	int _hasReachedSize;
};

