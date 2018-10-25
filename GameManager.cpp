#include "GameManager.h"
#include <iostream>
#include <algorithm>
#include "Definitions.h"
#include "Invader.h"

GameManager::GameManager()
{

}


GameManager::~GameManager()
{

}

void GameManager::AddSprite(SpriteObject* sprite)
{
	sprites.push_back(sprite);
}

void GameManager::AddSpriteToGarbage(SpriteObject * spritePtr)
{
	garbageCollection.push_back(spritePtr);
}

void GameManager::Update(float dt)
{
	if (getPaused() == true) {
		//return;
	}

	if (getReachedSide() == true) {
		setVerticalOffset(15);
		setReachedSide(false);
	}
	else {
		setVerticalOffset(0);
	}

	for (auto sprite : sprites) {
		sprite->Update(dt);

		if (sprite->GetSpriteType() == DEFENCE) {
			continue;
		}

		if (sprite->GetSprite().getPosition().x < 0 || sprite->GetSprite().getPosition().y < 0
			|| sprite->GetSprite().getPosition().x > SCREEN_WIDTH || sprite->GetSprite().getPosition().y > SCREEN_HEIGHT - 100) {
			AddSpriteToGarbage(sprite);
			continue;
		}

		for (auto spriteCopy : sprites) {
			if (sprite == spriteCopy) {
				continue;
			}

			if (GetSpriteManager().CanCollide(sprite->GetSpriteType(), spriteCopy->GetSpriteType()) == false) {
				continue;
			}

			if (GetSpriteManager().CloseDistance(sprite->GetSprite().getPosition(), spriteCopy->GetSprite().getPosition()) == false) {
				continue;
			}
						
			if (sprite != spriteCopy && sprite->GetSprite().getGlobalBounds().intersects(spriteCopy->GetSprite().getGlobalBounds())) {
				AddSpriteToGarbage(sprite);
				AddSpriteToGarbage(spriteCopy);
				break;
			}
		}

	}

	for (auto garbageSprite : garbageCollection) {
		for (auto sprite = sprites.begin(); sprite != sprites.end();) {
			if ((*sprite) == garbageSprite) {
				(*sprite)->Delete();
				delete (*sprite);
				sprite = sprites.erase(sprite);
			}
			else {
				++sprite;
			}
		}
	}

	garbageCollection.clear(); 
}

void GameManager::Draw()
{
	for (auto sprite : sprites) {
		sprite->Draw();
	}
}

void GameManager::UpdateInput(float dt)
{	
	for (auto sprite : sprites) {
		sprite->UpdateInput(dt);
	}
}

bool GameManager::Clear()
{
	clearInvaderIndex();
	garbageCollection.clear();

	for (auto sprite = sprites.begin(); sprite != sprites.end();) {
			(*sprite)->Delete();
			delete (*sprite);
			sprite = sprites.erase(sprite);

	}
	return true;
}

int GameManager::getTotalSprites()
{
	return sprites.size();
}

void GameManager::setFPS(float fps)
{
	_fps = fps;
}

float GameManager::getFPS()
{
	return _fps;
}

void GameManager::CheckDirectionClear(int direction, bool strictObject)
{
	std::vector<SpriteObject*>::iterator spritesItr;
	std::vector<SpriteObject*> spritesCopy = sprites;

	bool found = false;

	for (auto sprite : sprites) {
		for (auto spriteItr = sprites.rbegin(); spriteItr != sprites.rend();) {
			if (sprite != (*spriteItr) && (*spriteItr)->GetCollision().CheckIfDirectionFree((sprite)->GetCollision(), 3) == true) {
				found = true;
			}
		}

		if (found == true) {
			sprite->SetCanFire(false);
		}
		else if (found == false) {
			sprite->SetCanFire(true);
		}
	}

}

void GameManager::setVerticalOffset(int value)
{
	_verticalOffset = value;
}

int GameManager::getVerticalOffset()
{
	return _verticalOffset;
}

int GameManager::getScore()
{
	return _score;
}

void GameManager::setScore(int value)
{
	_score = value;
}

int GameManager::getHealth()
{
	return _health;
}

void GameManager::setHealth(int value)
{
	_health = value;
}

bool GameManager::getReachedSide()
{
	return _hasReachedSize;
}

void GameManager::setReachedSide(bool value)
{
	_hasReachedSize = value;
	
}

void GameManager::addInvaderIndex(int index)
{
	invaderIndex.push_back(index);
}

void GameManager::removeInvaderIndex(int index)
{
	invaderIndex.erase(std::remove(invaderIndex.begin(), invaderIndex.end(), index), invaderIndex.end());
}

bool GameManager::indexExist(int index)
{
	if (std::find(invaderIndex.begin(), invaderIndex.end(), index) != invaderIndex.end()) {
		return true;
	}
	return false;
}

void GameManager::clearInvaderIndex()
{
	Invader::setTotal(0);
	invaderIndex.clear();
}

void GameManager::setPaused(bool value)
{
	isPaused = value;
}

bool GameManager::getPaused()
{
	return isPaused;
}

