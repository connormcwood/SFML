#pragma once
#include "Observer.h"
#include "SpriteObject.h"
#include "Game.h"
#include <iostream>
#include <string>

class DeathObserver : public Observer
{
public:
	DeathObserver(SpriteObject* spriteObj, GameDataRef data);
	~DeathObserver();
	void SetSpriteObj(SpriteObject* spriteObj);
	SpriteObject* GetSpriteObj();

	void Update() {
		GetSpriteObj()->onDeath();
		//this->_data->manager.removeInvaderIndex(GetSpriteObj()->getIndex());
	}
private:
	GameDataRef _data;
	SpriteObject* _sprite;
};

