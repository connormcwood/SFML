#include "DeathObserver.h"
DeathObserver::DeathObserver(SpriteObject * spriteObj, GameDataRef data)
	: _data(data)
{
	SetSpriteObj(spriteObj);
	spriteObj->Attach(this);
}
DeathObserver::~DeathObserver()
{

}

void DeathObserver::SetSpriteObj(SpriteObject * spriteObj)
{
	_sprite = spriteObj;
}

SpriteObject * DeathObserver::GetSpriteObj()
{
	return _sprite;
}
