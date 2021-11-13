#pragma once
#include <SDL.h>
#include <string>
#include "Texture.h"
#include "GameEngine.h"
#include <map>

class TextureManager {

public:

	TextureManager(GameEngine* gameEngineRef) 
	{
		myGameEngine = myGameEngine;
		renderTarget = SDL_CreateRenderer(myGameEngine->GetWindow()->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	};

	~TextureManager() 
	{
		std::map<std::string, Texture*>::iterator it;
		for (it = textureMap.begin(); it != textureMap.end(); it++) 
		{
			delete it->second;
			textureMap.erase(it);
		}

		delete myGameEngine;
		delete renderTarget;
	};

	void Init();
	void Draw();
	void DrawFrame();
	Texture* LoadTexture(std::string id, std::string filePath);

private:
	
	std::map<std::string, Texture*> textureMap{};
	GameEngine* myGameEngine{ nullptr };
	SDL_Renderer* renderTarget{ nullptr };
};
