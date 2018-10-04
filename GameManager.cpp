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
	std::vector<SpriteObject*> spritesCopy = sprites; //Copy The Vector As The Vector Memory May Change When New Sprites Are Added
	std::vector<SpriteObject*>::iterator spritesItr;

	std::vector<SpriteObject*> spritesCopyTwo = spritesCopy; //Copy The Vector As The Vector Memory May Change When New Sprites Are Added
	std::vector<SpriteObject*>::iterator spritesItrTwo;

	sf::Vector2f direction;

	if (getReachedSide() == true) {
		setVerticalOffset(15);
		setReachedSide(false);
	}

	int iteration = 0;
	for (spritesItr = spritesCopy.begin(); spritesItr != spritesCopy.end(); spritesItr++) {
		iteration++;
		(*spritesItr)->Update(dt);
		if ((*spritesItr)->GetSprite().getPosition().x < 0 || (*spritesItr)->GetSprite().getPosition().y < 0
			|| (*spritesItr)->GetSprite().getPosition().x > SCREEN_WIDTH || (*spritesItr)->GetSprite().getPosition().y > SCREEN_HEIGHT - 100) {
			AddSpriteToGarbage(*spritesItr);
			continue;
		}
		for (spritesItrTwo = spritesCopyTwo.begin(); spritesItrTwo != spritesCopyTwo.end(); spritesItrTwo++) {
			if ((*spritesItr) != (*spritesItrTwo) && (*spritesItr)->GetCollision().CheckCollision((*spritesItrTwo)->GetCollision(), direction, 1.0f)) {
				AddSpriteToGarbage(*spritesItr);
				AddSpriteToGarbage(*spritesItrTwo);
			}
		}
	}
	setVerticalOffset(0);

	std::vector<SpriteObject*>::iterator garbageCollectionItr;
	std::vector<SpriteObject*>::iterator spriteRealItr;
	for (garbageCollectionItr = garbageCollection.begin(); garbageCollectionItr != garbageCollection.end(); garbageCollectionItr++) {
		for (spriteRealItr = sprites.begin(); spriteRealItr != sprites.end();) {	
			if (*garbageCollectionItr == *spriteRealItr) {
				(*spriteRealItr)->Delete();
				delete (*spriteRealItr);
				//delete * spriteRealItr;				
				spriteRealItr = sprites.erase(spriteRealItr);				
			}
			else {
				++spriteRealItr;
			}
		}
	}
	garbageCollection.clear();
}

void GameManager::Draw()
{
	spritesCopy = sprites;
	
	for (spritesItr = spritesCopy.begin(); spritesItr != spritesCopy.end(); spritesItr++) {
		SpriteObject* object = *spritesItr;
		(object)->Draw();
	}
}

void GameManager::UpdateInput(float dt)
{	
	spritesCopy = sprites;

	for (spritesItr = spritesCopy.begin(); spritesItr != spritesCopy.end(); spritesItr++) {
		SpriteObject* object = *spritesItr;
		(object)->UpdateInput(dt);
	}
}

bool GameManager::Clear()
{
	clearInvaderIndex();
	garbageCollection.clear();
	std::vector<SpriteObject*>::iterator spritesItr;
	for (spritesItr = sprites.begin(); spritesItr != sprites.end();) {
		delete * spritesItr;
		spritesItr = sprites.erase(spritesItr);
	}
	return true;
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

	for (std::vector<SpriteObject*>::reverse_iterator spriteItr = spritesCopy.rbegin();
		spriteItr != spritesCopy.rend(); ++spriteItr) {
		for (std::vector<SpriteObject*>::reverse_iterator spriteItrCopy = spritesCopy.rbegin();
			spriteItrCopy != spritesCopy.rend(); ++spriteItrCopy) {		
			if (spriteItrCopy != spriteItr) {
				if ((*spriteItr)->GetCollision().CheckIfDirectionFree((*spriteItrCopy)->GetCollision(), 3) == true) {
					found = true;
				}
			}
		}

		if (found == true) {
			(*spriteItr)->SetCanFire(false);
		}
		else if (found == false) {
			(*spriteItr)->SetCanFire(true);
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
	std::cout << "Score:" << _score << std::endl;
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

