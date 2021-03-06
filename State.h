#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"

class State
{
public:
	virtual void Init() = 0;
	virtual void Destroy() = 0;

	virtual void HandleInput(float dt) = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw(float dt) = 0;


	virtual void Pause() { }
	virtual void Resume() { }
};