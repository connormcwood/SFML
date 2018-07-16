#include "GameManager.h"
#include <iostream>


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
		//std::cout << iteration << std::endl;
		for (spritesItrTwo = spritesCopyTwo.begin(); spritesItrTwo != spritesCopyTwo.end(); spritesItrTwo++) {
			SpriteObject* secObject = *spritesItrTwo;
			if (*spritesItr != *spritesItrTwo && object->GetCollision().CheckCollision(secObject->GetCollision(), direction, 1.0f)) {
				AddSpriteToGarbage(*spritesItr);
				AddSpriteToGarbage(*spritesItrTwo);
				
				/*spritesItrTwo = spritesCopyTwo.erase(spritesItrTwo);
				if (spritesItrTwo != spritesCopyTwo.begin()) {
					spritesItrTwo = std::prev(spritesItrTwo);
					continue;
				}*/
			}
		}
	}
	
	std::vector<SpriteObject*>::iterator garbageCollectionItr;
	for (garbageCollectionItr = garbageCollection.begin(); garbageCollectionItr != garbageCollection.end(); garbageCollectionItr++) {
		SpriteObject* spritePtr = *garbageCollectionItr;
		sprites.erase(std::remove(sprites.begin(), sprites.end(), spritePtr), sprites.end());
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
