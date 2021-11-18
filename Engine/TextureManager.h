#pragma once

//#ifndef TEXTUREMANAGER_M
//#define TEXTUREMANAGER_M

#include <SDL.h>
#include <string>
#include "Texture.h"
#include "GameEngine.h"
#include <map>

class TextureManager {

public:

	~TextureManager() 
	{
		std::map<std::string, Texture*>::iterator it;

		for (it = textureMap.begin(); it != textureMap.end(); it++) 
		{
			delete it->second;
		}

		textureMap.clear();
		delete sInstance;
		delete renderTarget;
	};

	static TextureManager* GetInstance() { return sInstance = (sInstance != nullptr) ? sInstance : new TextureManager(); }

	bool DrawTexture(std::string id, int y, int x, int width, int height, double angle, bool flipHor = false);
	void DropTexture(std::string id);
	void DrawFrame(std::string id, int y, int x, int width, int height, double angle, int row, int frame, bool flipHor);
	Texture* LoadTexture(std::string id, std::string filePath);
	

private:

	TextureManager()
	{
		renderTarget = SDL_CreateRenderer(GameEngine::GetInstance()->GetWindow()->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	};

	static TextureManager* sInstance;
	std::map<std::string, Texture*> textureMap{};
	SDL_Renderer* renderTarget{ nullptr };
	
};

//#endif // TEXTUREMANAGER_M