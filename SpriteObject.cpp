#include "SpriteObject.h"
#include "DeathObserver.h"
#include <string>
#include <iostream>

SpriteObject::SpriteObject()
{

}


SpriteObject::~SpriteObject()
{

}

void SpriteObject::Attach(Observer * obs)
{
	observerList.push_back(obs);
}

void SpriteObject::Detach(Observer * obs)
{
	observerList.erase(std::remove(observerList.begin(), observerList.end(), obs), observerList.end());
}

void SpriteObject::Detach()
{
	for (Observer* obsItr : observerList) {
		std::cout << "Deleted: " << obsItr << std::endl;
	}
}

void SpriteObject::Notify()
{
	for (Observer* obsItr : observerList)
		obsItr->Update();
}

bool SpriteObject::GetCollide()
{
	return _canCollide;
}

void SpriteObject::SetCollide(bool value)
{
	_canCollide = value;
}
