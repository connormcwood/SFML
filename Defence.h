#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteObject.h"
#include "Game.h"

class Defence :
	public SpriteObject
{
public:
	Defence(GameDataRef data, int index, float startX, float startY);
	~Defence();

	void Update(float dt);
	void UpdateInput(float dt);
	void Draw();
	void Delete();
	void onDeath();
	void UpdateAnimation() { }
	bool onCollision() {
		SetHealth(GetHealth() - 1);
		setAnimationIndex(getAnimationIndex() + 1);
		updateSpriteTextureRect();
		if (GetHealth() > 1) {
			return false;
		}
	}

	void updateSpriteTextureRect() {
		_collisionSprite.setTextureRect(_retrievedAnimation[getAnimationIndex()]);
	}

	int getAnimationIndex() {
		return _animationIndex;
	}
	void setAnimationIndex(int animationIndex) {
		_animationIndex = animationIndex;
	}

	int GetHealth();
	void SetHealth(int value);

	int getIndex() { return _index; }

	Collision GetCollision() { return Collision(_sprite); }
	sf::Sprite& GetSprite() { return _sprite; }
	sf::Sprite GetCollisionSprite() { return _collisionSprite; }
	std::map<int, sf::IntRect> _retrievedAnimation;
	spriteTypes GetSpriteType() { return DEFENCE; }

private:
	GameDataRef _data;
	sf::Sprite _sprite;
	sf::Sprite _collisionSprite;
	sf::Clock _track;
	sf::Clock _missleCooldown;
	sf::Clock _restartCooldown;

	std::string texture_name;

	int _index;
	int _health = 5;
	int _animationIndex = 0;
};

