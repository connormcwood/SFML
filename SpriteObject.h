#pragma once
#include <SFML\Audio.hpp>
#include "Definitions.h"
#include "Collision.h"
#include "Observer.h"
#include <vector>
#include <map>

class Observer;

enum spriteTypes {
	MISSLE,
	CHARACTER,
	DEFENCE,
	INVADER,
	UFO
};

class SpriteObject
{

public:
	SpriteObject();
	virtual ~SpriteObject() = 0;

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual void UpdateInput(float dt) = 0;
	virtual sf::Sprite& GetSprite() = 0;
	virtual Collision GetCollision() = 0;
	virtual void Delete() = 0;
	virtual int getIndex() = 0;
	virtual void onDeath() = 0;
	virtual bool onCollision() = 0;
	virtual void UpdateAnimation() = 0;

	virtual spriteTypes GetSpriteType() = 0;
	
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

	bool GetCollide();
	void SetCollide(bool value);

	void SetSpriteObjectPtr(SpriteObject* spriteObjectPtr) {
		_spriteObjectPtr = spriteObjectPtr;
	}
	SpriteObject* GetSpriteObjectPtr() {
		return _spriteObjectPtr;
	}

protected: 
	bool isAlive = true;
	bool _canFire = false;
	bool _canCollide = false;
	int health;
	SpriteObject* _spriteObjectPtr;
private:
	std::vector<Observer*> observerList;
	sf::Sound sound;
};


