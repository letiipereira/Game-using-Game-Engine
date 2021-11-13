#pragma once
#include <SDL.h>
#include "Window.h"

class Texture

{
public:

	Texture(SDL_Surface* surface, SDL_Renderer* targetRederer) 
	{

		textureSDL = SDL_CreateTextureFromSurface(targetRederer, surface);
	};
	~Texture() 
	{
		SDL_DestroyTexture(textureSDL);
	};


private:

	SDL_Texture* textureSDL{ nullptr };

};