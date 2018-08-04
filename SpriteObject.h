#pragma once
#include <SFML\Audio.hpp>
#include "Collision.h"
#include "Observer.h"
#include <vector>

class Observer;

class SpriteObject
{
	std::vector<Observer*> observerList;
public:
	SpriteObject();
	~SpriteObject();

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual void UpdateInput(float dt) = 0;
	virtual sf::Sprite& GetSprite() = 0;
	virtual Collision GetCollision() = 0;
	virtual void Delete() = 0;
	virtual int getIndex() = 0;

	virtual void onDeath() = 0;

	bool GetCanFire() {
		return _canFire;
	}
	void SetCanFire(bool value) {
		_canFire = value;
	}

	bool GetAlive() {
		return isAlive;
	}
	void SetAlive(bool _isAlive) {
		isAlive = _isAlive;
		Notify();
	}

	void Attach(Observer* obs);
	
	void Detach();
	void Detach(Observer* obs);
	void Notify();

protected: 
	bool isAlive = true;
	bool _canFire = false;
	
	sf::Sound sound;
};


