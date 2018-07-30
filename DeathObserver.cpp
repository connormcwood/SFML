#include "DeathObserver.h"
DeathObserver::DeathObserver(SpriteObject * spriteObj, GameDataRef data)
	: _data(data)
{
	SetSpriteObj(spriteObj);
	spriteObj->Attach(this);
}
DeathObserver::~DeathObserver()
{
	std::cout << "Deleted Death Observer" << std::endl;
}

void DeathObserver::SetSpriteObj(SpriteObject * spriteObj)
{
	_sprite = spriteObj;
}

SpriteObject * DeathObserver::GetSpriteObj()
{
	return _sprite;
}
