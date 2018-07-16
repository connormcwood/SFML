#pragma once
#include "Collision.h"

class SpriteObject
{
public:
	SpriteObject();
	~SpriteObject();

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual void UpdateInput(float dt) = 0;
	virtual Collision GetCollision() = 0;
};

