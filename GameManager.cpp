#include "GameManager.h"
#include <iostream>
#include "Definitions.h"

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

	int iteration = 0;
	for (spritesItr = spritesCopy.begin(); spritesItr != spritesCopy.end(); spritesItr++) {
		iteration++;
		SpriteObject* object = *spritesItr;
		object->Update(dt);
		if (object->GetSprite().getPosition().x < 0 || object->GetSprite().getPosition().y < 0 
			|| object->GetSprite().getPosition().x > SCREEN_WIDTH || object->GetSprite().getPosition().y > SCREEN_HEIGHT) {
			AddSpriteToGarbage(*spritesItr);
			continue;
		}
		for (spritesItrTwo = spritesCopyTwo.begin(); spritesItrTwo != spritesCopyTwo.end(); spritesItrTwo++) {
			SpriteObject* secObject = *spritesItrTwo;
			if (*spritesItr != *spritesItrTwo && object->GetCollision().CheckCollision(secObject->GetCollision(), direction, 1.0f)) {
				AddSpriteToGarbage(*spritesItr);
				AddSpriteToGarbage(*spritesItrTwo);
			}
		}
	}
	
	std::vector<SpriteObject*>::iterator garbageCollectionItr;
	std::vector<SpriteObject*>::iterator spriteRealItr;
	for (garbageCollectionItr = garbageCollection.begin(); garbageCollectionItr != garbageCollection.end(); garbageCollectionItr++) {
		SpriteObject* spritePtr = *garbageCollectionItr;
		for (spriteRealItr = sprites.begin(); spriteRealItr != sprites.end();) {
			if (*garbageCollectionItr == *spriteRealItr) {
				spriteRealItr = sprites.erase(spriteRealItr);
			}
			else {
				++spriteRealItr;
			}
		}
	}


}

void GameManager::Draw()
{
	std::vector<SpriteObject*> spritesCopy = sprites; //Copy The Vector As The Vector Memory May Change When New Sprites Are Added
	std::vector<SpriteObject*>::iterator spritesItr;

	for (spritesItr = spritesCopy.begin(); spritesItr != spritesCopy.end(); spritesItr++) {
		SpriteObject* object = *spritesItr;
		object->Draw();
	}
}

void GameManager::UpdateInput(float dt)
{	
	std::vector<SpriteObject*> spritesCopy = sprites; //Copy The Vector As The Vector Memory May Change When New Sprites Are Added
	std::vector<SpriteObject*>::iterator spritesItr;

	for (spritesItr = spritesCopy.begin(); spritesItr != spritesCopy.end(); spritesItr++) {
		SpriteObject* object = *spritesItr;
		object->UpdateInput(dt);
	}
}

void GameManager::SetFPS(float fps)
{
	_fps = fps;
}

float GameManager::GetFPS()
{
	return _fps;
}

bool GameManager::CheckDirectionClear(SpriteObject* sprite, int direction, bool strictObject)
{
	std::vector<SpriteObject*>::iterator spritesItr;
	for (spritesItr = sprites.begin(); spritesItr != sprites.end(); spritesItr++) {
		SpriteObject* object = *spritesItr;
		if (sprite != object) {
			if (sprite->GetCollision().CheckIfDirectionFree(object->GetCollision(), 3) == true) {
				return true;
			} 
		}
	}
	return false;
}
