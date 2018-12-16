#pragma once
#include <SFML\Graphics.hpp>
#include "SpriteManager.h"
#include "SpriteObject.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	void AddSprite(SpriteObject* sprite);
	void AddSpriteToGarbage(SpriteObject* spritePtr);

	SpriteManager GetSpriteManager() { return spriteManager;  }

	void Update(float dt);
	void Draw();
	void UpdateInput(float dt);
	bool Clear();

	int getTotalSprites();

	void setFPS(float fps);
	float getFPS();

	void CheckDirectionClear(int direction, bool strictObject);

	void setVerticalOffset(int value);
	int	getVerticalOffset();

	int getHealth();
	void setHealth(int value);

	int getScore();
	void setScore(int value);

	bool getReachedSide();
	void setReachedSide(bool value);

	void addInvaderIndex(int index);
	void removeInvaderIndex(int index);
	bool indexExist(int index);
	void clearInvaderIndex();

	void setPaused(bool value);
	bool getPaused();

	sf::Clock _time;
	sf::Clock _animation;
	sf::Clock _missleCooldown;

	bool canShoot() {
		if (_missleCooldown.getElapsedTime().asSeconds() > 3) {
			return true;
		}
		return false;
	}

	bool canAnimate() {
		if (_animation.getElapsedTime().asSeconds() > 0.5) {
			return true;
		}
		return false;
	}

	void checkShootReset() {
		if (_missleCooldown.getElapsedTime().asSeconds() > 3) {
			_missleCooldown.restart();
		}
	}

	void checkAnimateReset() {
		if (_animation.getElapsedTime().asSeconds() > 0.5) {
			_animation.restart();
		}
	}

private:
	std::vector<SpriteObject*> sprites;
	std::vector<SpriteObject*> garbageCollection;
	std::vector<int> invaderIndex;
	float _fps = 0;



	int _score = 0;
	int _health = 3;

	int _verticalOffset;

	int _hasReachedSize;

	bool isPaused = false;

	SpriteManager spriteManager = SpriteManager();
};

