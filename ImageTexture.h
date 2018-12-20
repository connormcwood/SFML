#pragma once
#include "Texture.h"

class ImageTexture :
	public Texture
{
private:
	AssetManager * assetManager;

	const pugi::char_t * _masterName = "textureatlas";
	const pugi::char_t * _parentName = "regularTexture";
	const pugi::char_t * _childName = "subtexture";
public:
	ImageTexture();
	~ImageTexture();
	
	void LoadAssetManager(AssetManager * _assetManager);
	void CreateTextures(std::string name, std::string fileName, const char* xmlFileName);
	AssetManager * GetManager() { return assetManager; }

	const pugi::char_t * GetMasterProperty() { return _masterName; }
	const pugi::char_t * GetParentProperty() { return _parentName; }
	const pugi::char_t * GetChildProperty() { return _childName; }
};
