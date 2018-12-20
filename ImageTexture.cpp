#include "ImageTexture.h"

ImageTexture::ImageTexture()
{
}


ImageTexture::~ImageTexture()
{
}

void ImageTexture::LoadAssetManager(AssetManager * _assetManager)
{
	assetManager = _assetManager;
};

void ImageTexture::CreateTextures(std::string name, std::string fileName, const char* xmlFileName)
{
	pugi::xml_document doc;

	if (!doc.load_file(xmlFileName)) {
		std::cout << "Couldnt Load" << std::endl;
	}
	pugi::xml_node textures = doc.child(GetMasterProperty());
	for (pugi::xml_node group = textures.child(GetParentProperty()); group; group = group.next_sibling(GetParentProperty())) {
		for (pugi::xml_node texture = group.child(GetChildProperty()); texture; texture = texture.next_sibling(GetChildProperty()))
		{
			int x = std::stoi(texture.attribute("x").value());
			int y = std::stoi(texture.attribute("y").value());
			int width = std::stoi(texture.attribute("width").value());
			int height = std::stoi(texture.attribute("height").value());
			GetManager()->AddTexture(texture.attribute("name").value(), fileName, x, y, width, height);
		}
	}
};
