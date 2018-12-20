#include "AnimationTexture.h"

AnimationTexture::AnimationTexture()
{
}


AnimationTexture::~AnimationTexture()
{
}

void AnimationTexture::LoadAssetManager(AssetManager * _assetManager)
{
	assetManager = _assetManager;
}

void AnimationTexture::CreateTextures(std::string name, std::string fileName, const char * xmlFileName)
{
	pugi::xml_document doc;

	if (!doc.load_file(xmlFileName)) {
		std::cout << "Couldnt Load" << std::endl;
	}
	pugi::xml_node textures = doc.child(GetMasterProperty());
	for (pugi::xml_node group = textures.child(GetParentProperty()); group; group = group.next_sibling(GetParentProperty())) {
		std::string name = group.attribute("name").value();
		for (pugi::xml_node texture = group.child(GetChildProperty()); texture; texture = texture.next_sibling(GetChildProperty()))
		{
			int x = std::stoi(texture.attribute("x").value());
			int y = std::stoi(texture.attribute("y").value());
			int width = std::stoi(texture.attribute("width").value());
			int height = std::stoi(texture.attribute("height").value());
			GetManager()->SetAnimation(name, sf::IntRect(x, y, width, height));
		}

		GetManager()->AddTexture(name, fileName);
	}
}
