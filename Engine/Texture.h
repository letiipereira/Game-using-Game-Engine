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
		std::cout << SDL_GetError() << std::endl;
	};

	SDL_Texture* GetSDLTexture();

	~Texture() 
	{
		SDL_DestroyTexture(textureSDL);
	};


private:

	SDL_Texture* textureSDL;

};