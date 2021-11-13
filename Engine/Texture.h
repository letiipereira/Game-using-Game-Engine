#pragma once
#include <SDL.h>

class Texture

{
public:

	Texture(SDL_Surface* surface) 
	{
		textureSDL = SDL_CreateTextureFromSurface(window, surface);
	};
	~Texture() 
	{
		SDL_DestroyTexture(textureSDL);
	};


private:

	SDL_Texture* textureSDL{ nullptr };

};