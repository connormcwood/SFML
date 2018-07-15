#pragma once

class SpriteObject
{
public:
	SpriteObject();
	~SpriteObject();

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual void UpdateInput(float dt) = 0;
};

