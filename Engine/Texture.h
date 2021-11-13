#pragma once
#include <SDL.h>
#include "Window.h"
#include <iostream>

class Texture

{
public:

	Texture(SDL_Surface* surface, SDL_Renderer* targetRederer) 
	{
		textureSDL = SDL_CreateTextureFromSurface(targetRederer, surface);
		if (textureSDL == nullptr)
			std::cout << "Error creating SDL Texture";
	};

	SDL_Texture* GetSDLTexture();

	~Texture() 
	{
		SDL_DestroyTexture(textureSDL);
	};


private:

	SDL_Texture* textureSDL{ nullptr };

};