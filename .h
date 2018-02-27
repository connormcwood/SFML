#pragma once
#include "State.h"
class MainMenu :
	public State
{
public:
	MainMenu(GameDataRef data);
	~MainMenu();

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);
};

