#pragma once

//#ifndef TEXTUREMANAGER_M
//#define TEXTUREMANAGER_M

#include <string>
#include "Texture.h"
#include "GameEngine.h"
#include <map>
#include "Transform.h"

class TextureManager {

public:

	TextureManager();
	~TextureManager();

	static TextureManager* GetInstance() { return sInstance = (sInstance != nullptr) ? sInstance : new TextureManager(); }

	void DrawTexture(std::string id, Transform* transform, bool flipHor = false);
	void Render();
	void Clear();
	void DropTexture(std::string id);
	void DrawFrame(std::string id, Transform* transform, int rowCurrent = 1, int frameCurrent = 1, int rowTotal = 1, int frameTotal = 1, double angle = 0, bool flipHor = false);
	Texture* GetTexture(std::string id);
	Texture* LoadTexture(std::string id, std::string filePath);
	

private:

	static TextureManager* sInstance;
	std::map<std::string, Texture*> textureMap{};
	
};

//#endif // TEXTUREMANAGER_M