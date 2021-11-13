#pragma once
#include <SDL.h>
#include <string>
#include "Texture.h"
#include <map>

class TextureManager {

public:

	TextureManager() {};

	~TextureManager() 
	{
		std::map<std::string, Texture*>::iterator it;
		for (it) { delete tex; }
	};

	void Init();
	void Draw();
	void DrawFrame();
	Texture* LoadTexture(std::string filePath);

private:
	
	std::map<std::string, Texture*> textureMap;
};
