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

	~TextureManager();

	static TextureManager* GetInstance() { return sInstance = (sInstance != nullptr) ? sInstance : new TextureManager(); }

	bool DrawTexture(std::string id, Transform* transform, bool flipHor = false);
	void Render();
	void Clear();
	void DropTexture(std::string id);
	void DrawFrame(std::string id, Transform* transform, int width, int height, double angle, int row, int frame, bool flipHor = false);
	Texture* GetTexture(std::string id);
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