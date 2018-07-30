#pragma once
#include "SpriteObject.h"



class Observer
{	
public:
	Observer();
	~Observer();
	virtual void Update() = 0;
};


