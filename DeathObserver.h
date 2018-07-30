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
	SpriteObject* _sprite;
	void Update() {
		std::cout << GetSpriteObj()->getIndex() << std::endl;
		this->_data->manager.removeInvaderIndex(GetSpriteObj()->getIndex());
	}
private:
	GameDataRef _data;
};

