#pragma once
#include "AssetManager.h"
#include "pugixml.hpp"
#include <iostream>

class Texture
{
public:
	Texture();
	~Texture();

	virtual void LoadAssetManager(AssetManager * _assetManager) = 0;
	virtual void CreateTextures(std::string name, std::string fileName, const char* xmlFileName) = 0;
	virtual AssetManager * GetManager() = 0;
	virtual const pugi::char_t * GetMasterProperty() = 0;
	virtual const pugi::char_t * GetParentProperty() = 0;
	virtual const pugi::char_t * GetChildProperty() = 0;
};
